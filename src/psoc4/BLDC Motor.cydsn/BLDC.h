/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#ifndef BLDC_H
#define BLDC_H

#include "project.h"
#include "stdlib.h"
#include "math.h"
#include "stdio.h"

struct BLDC_4_00
{
    uint32 freq;
    float maxspeed;
    float maxrate;
    float p_speed;
    float wait;
    
    uint8 inttrig;
    uint8 refstate,comtable[6], seqCW[8], seqCCW[8];
    uint8 n_sections, intfactor;
    uint8 maxDC;
    unsigned long delta;
    
    struct BLDC_motconfig{
        uint8 u,v,w;
        struct BLDC_4_00_SD *A,*B,*C;
    }m;

};
struct BLDC_4_00 *intptr;

CY_ISR(isr_millis_Handler){
    static uint32 millis=0;
    Counter_micros_WriteCompare(Counter_micros_ReadCompare() + 1000);
    millis += 1;
    //Counter_micros_ClearInterrupt(Counter_micros_INTR_MASK_TC);
}

void hallinthandle(){
    static unsigned long prevtime = 0;
    if (!intptr->inttrig){
        intptr->inttrig = 1; 
        intptr->delta = Counter_micros_ReadCounter() - prevtime;
        prevtime = Counter_micros_ReadCounter();
  } 
}
CY_ISR(isr_ur_Handler){
    
//    if (!intptr->inttrig){
//        intptr->inttrig = 1; 
//        intptr->delta = Counter_micros_ReadCounter() - prevtime;
//        prevtime = Counter_micros_ReadCounter();
//    } 
    hallinthandle();
    u_ClearInterrupt();
}

CY_ISR(isr_vr_Handler){
//    static unsigned long prevtime = 0;
    
//    if (!intptr->inttrig){
//        intptr->inttrig = 1; 
//        intptr->delta = Counter_micros_ReadCounter() - prevtime;
//        prevtime = Counter_micros_ReadCounter();
//  } 
    hallinthandle();
    v_ClearInterrupt();
}

CY_ISR(isr_wr_Handler){
    hallinthandle();
    w_ClearInterrupt();
}

CY_ISR(isr_uf_Handler){
    hallinthandle();
    u_ClearInterrupt();
}

CY_ISR(isr_vf_Handler){
    hallinthandle();
    v_ClearInterrupt();
}

CY_ISR(isr_wf_Handler){
    hallinthandle();
    w_ClearInterrupt();
}

void inhA(struct BLDC_4_00 *p){

    INHA_Write(0);
}

void inhB(struct BLDC_4_00 *p){

    INHB_Write(0);
}

void inhC(struct BLDC_4_00 *p){

    INHC_Write(0);
}

void activeA(struct BLDC_4_00 *p){

    INHA_Write(1);
}

void activeB(struct BLDC_4_00 *p){

    INHB_Write(1);
}

void activeC(struct BLDC_4_00 *p){

    INHC_Write(1);
}

//CY_ISR(isr_u_Handler){
//    
//    
//
//}

void BLDC_4_00_init(struct BLDC_4_00 *p, float maxspeed, float maxrate, uint32 f, uint8 npoles){

    PWM_A_WritePeriod(48000000/f);
    PWM_B_WritePeriod(48000000/f);
    PWM_C_WritePeriod(48000000/f);
    p->freq = f;                    //look into frequencyy
    p->wait = 1/(float)(f) *1000.0;
    p->maxspeed = maxspeed*48;
    p->maxrate = maxrate;
    p->p_speed = 0;
    
    npoles = 8;
    p->n_sections = npoles;
    p->maxDC = 20;
    for (int i = 0; i<6; i++){
        p->comtable[i] = i+1;
    }
    p->seqCW[0] =  0;
    p->seqCW[1] =  3;
    p->seqCW[2] =  6;
    p->seqCW[3] =  2;
    p->seqCW[4] =  5;
    p->seqCW[5] =  1;
    p->seqCW[6] =  4;
    p->seqCW[7] =  0;
    
    p->seqCCW[0] = 0;
    p->seqCCW[1] = 5;
    p->seqCCW[2] = 3;
    p->seqCCW[3] = 1;
    p->seqCCW[4] = 6;
    p->seqCCW[5] = 4;
    p->seqCCW[6] = 1;
    p->seqCCW[7] = 0;
    
    PWM_A_Start();
    PWM_B_Start();
    PWM_C_Start();
    inhA(p);
    inhB(p);
    inhC(p);
    
}

void setspeedA(struct BLDC_4_00 *p, float sped){

    float speed = /*4800 -*/ (sped*48);
    float temp =((fabs(speed))/p->maxspeed);
    PWM_A_WriteCompare(((temp < 0)?0:temp)*PWM_A_ReadPeriod());
}

void setspeedB(struct BLDC_4_00 *p, float sped){

    float speed = sped*48;
    float temp =((fabs(speed))/p->maxspeed);
    PWM_B_WriteCompare(((temp < 0)?0:temp)*PWM_B_ReadPeriod());
}

void setspeedC(struct BLDC_4_00 *p, float sped){

    float speed = /*4800 -*/ (sped*48);
    float temp =((fabs(speed))/p->maxspeed);
    PWM_C_WriteCompare(((temp < 0)?0:temp)*PWM_C_ReadPeriod());
}

void startmotorA(struct BLDC_4_00 *p){

    activeA(p);
    PWM_A_Start();
    setspeedA(p,p->p_speed);
}

void startmotorB(struct BLDC_4_00 *p){

    activeB(p);
    PWM_B_Start();
    setspeedB(p,p->p_speed);
}

void startmotorC(struct BLDC_4_00 *p)
{
    activeC(p);
    PWM_C_Start();
    setspeedC(p,p->p_speed);
}

//void setspeed_linA(struct BLDC_4_00 *p, float sp) //adjust clock and frequency (4800 thing)
//{
//    float temp_speed = sp - p->p_speed;
//    float iter = (fabs(temp_speed)/p->maxspeed)*(p->maxrate/p->wait)*100;
//    int int_iter=iter;
//    float del_pwm= temp_speed/int_iter;
//    float extr_wait = fmod(iter,1)*p->wait;
//    float pwm= p->p_speed;
//    for(int i=0;i<int_iter;i++)
//    {
//        pwm += del_pwm;
//        setspeedA(p,pwm);
//        CyDelay(p->wait);
//    }
//    if(extr_wait>1) CyDelay(extr_wait);
//    setspeedA(p,sp);
//    p->p_speed = sp;
//}
//
//void setspeed_linB(struct BLDC_4_00 *p, float sp)  //adjust clock and frequency (4800 thing)
//{
//    float temp_speed = sp - p->p_speed;
//    float iter = (fabs(temp_speed)/p->maxspeed)*(p->maxrate/p->wait)*100;
//    int int_iter=iter;
//    float del_pwm= temp_speed/int_iter;
//    float extr_wait = fmod(iter,1)*p->wait;
//    float pwm= p->p_speed;
//    for(int i=0;i<int_iter;i++)
//    {
//        pwm += del_pwm;
//        setspeedB(p,pwm);
//        CyDelay(p->wait);
//    }
//    if(extr_wait>1) CyDelay(extr_wait);
//    setspeedB(p,sp);
//    p->p_speed = sp;
//}
//
//void setspeed_linC(struct BLDC_4_00 *p, float sp)  //adjust clock and frequency (4800 thing)
//{
//    float temp_speed = sp - p->p_speed;
//    float iter = (fabs(temp_speed)/p->maxspeed)*(p->maxrate/p->wait)*100;
//    int int_iter=iter;
//    float del_pwm= temp_speed/int_iter;
//    float extr_wait = fmod(iter,1)*p->wait;
//    float pwm= p->p_speed;
//    for(int i=0;i<int_iter;i++)
//    {
//        pwm += del_pwm;
//        setspeedC(p,pwm);
//        CyDelay(p->wait);
//    }
//    if(extr_wait>1) CyDelay(extr_wait);
//    setspeedC(p,sp);
//    p->p_speed = sp;
//}

void stopmotorA(struct BLDC_4_00 *p)
{
    inhA(p);
    PWM_A_Stop();
}

void stopmotorB(struct BLDC_4_00 *p)
{
    inhB(p);
    PWM_B_Stop();
}

void stopmotorC(struct BLDC_4_00 *p)
{
    inhC(p);
    PWM_C_Stop();
}

void startmotor(struct BLDC_4_00* p, char intpin)
{
    intpin = 'A';
    p->inttrig = 0;
    startmotorA(p);
    startmotorB(p);
    startmotorC(p);
//    setspeed_linA(p,0);
//    setspeed_linB(p,0);
//    setspeed_linC(p,0);
    switch(intpin)
    {
        case 'u':
        {
                    isr_ur_StartEx(isr_ur_Handler);
                    isr_uf_StartEx(isr_uf_Handler);
                        p->intfactor = 2;
                        break;
        }
    
       case 'v':
        {  
                    isr_vr_StartEx(isr_vr_Handler);
                    isr_vf_StartEx(isr_vf_Handler);
                    p->intfactor = 2;
                    break;
        }
        case 'w':
        {
                    isr_wr_StartEx(isr_wr_Handler);
                    isr_wf_StartEx(isr_wf_Handler);
                    p->intfactor = 2;
                    break;
        }
        case 'A':
        {
            isr_ur_StartEx(isr_ur_Handler);
            isr_vr_StartEx(isr_vr_Handler);
            isr_wr_StartEx(isr_wr_Handler);
            isr_uf_StartEx(isr_uf_Handler);
            isr_vf_StartEx(isr_vf_Handler);
            isr_wf_StartEx(isr_wf_Handler);
            p->intfactor = 6;
            break;
        }
        default: p->intfactor = 6;
                break;
    }
}

void brake(struct BLDC_4_00 *p){
        inhA(p);
        inhB(p);
        inhC(p);
}

float commute_trapz(struct BLDC_4_00 *p, uint8 state, float dc){
    uint8 l = 0;
    if(dc>p->maxDC) dc=p->maxDC;
    if(dc>100) dc = 100;
    if(dc<0) dc=0;
    inhA(p);
    inhB(p);
    inhC(p);
    if(state == p->comtable[0]){//3 1
        inhA(p);
        setspeedC(p,0);
        setspeedB(p,dc);
        activeC(p);
        activeB(p);
        return(dc);
    }
    if(state==p->comtable[1]){//6   2
        inhC(p);
        setspeedB(p,0);
        setspeedA(p,dc);
        activeB(p);
        activeA(p);
        return(dc); 
    }
    if(state == p->comtable[2]){//2 3
        inhB(p);
        setspeedC(p,0);
        setspeedA(p,dc);
        activeC(p);
        activeA(p);
        return(dc);
    }
    if (state == p->comtable[3]){//5    4
        inhB(p);
        setspeedA(p,0);
        setspeedC(p,dc);
        activeA(p);
        activeC(p);
        return(dc);
    }
    if (state == p->comtable[4]){//1    5
        inhC(p);
        setspeedA(p,0);
        setspeedB(p,dc);
        activeA(p);
        activeB(p);
        return(dc);
    }
    if (state == p->comtable[5]){//4    6
        inhA(p);
        setspeedB(p,0);
        setspeedC(p,dc);
        activeB(p);
        activeC(p);
        return(dc);
    }
    if(state == 0 || state == 7){
        inhA(p);
        inhB(p);
        inhC(p);
        return(0);
    }
    return -1;
}

uint8 isinttrig(struct BLDC_4_00 *p){
//    printf("%d\n",p->inttrig);
    return(p->inttrig);
    
}

void clrint(struct BLDC_4_00 *p){
    p->inttrig = 0 ;
}

uint8 getstate(struct BLDC_4_00 *p){
    uint8 s=0;
    s = (s << 1) | u_Read();
    s = (s << 1) | v_Read();
    s = (s << 1) | w_Read();
    return s;
}

uint8 nextstate(struct BLDC_4_00 *p, uint8 s, uint8 dir){
    uint8 *seq=dir?p->seqCW:p->seqCCW;
//    uint8 i;
//    for(i = 0;i<6;i++){
//        if(seq[i] == s) break;  
//    }
    return seq[s];
}

void setcomtable(struct BLDC_4_00 *p, uint8_t *com){
    for (int i = 0; i<6; i++)
        p->comtable[i] = com[i];
}

void setseqCW(struct BLDC_4_00 *p, uint8 *sCW){
    for (int i = 0; i<6;i++){
        p->seqCW[i] = sCW[i];
    }
}

void setseqCCW(struct BLDC_4_00 *p,uint8 *sCCW){
    for (int i=0; i<6; i++){
        p->seqCCW[i] = sCCW[i];
    }
}

float rpm_btn_int(struct BLDC_4_00 *p){
    return(60/(p->n_sections*p->intfactor *p->delta*(1e-6)));
}

float del_btn_int(struct BLDC_4_00 *p)
{
    return (p->delta);
}
#endif

/* [] END OF FILE */