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
#include "BLDC.h"
#include "PID.h"

/********************************
 ***START printf() ACCOMODATION***
 *********************************/
 int _write(int file, char *ptr, int len)
 {
     (void) file ;
     int i ;
     for (i = 0 ; i < len ; i++) {
         UART_UartPutChar(*ptr++) ;
     }
     return len ;
 }
/********************************
 ****END printf() ACCOMODATION****
 *********************************/

#define PWMFREQ 10000
#define FLEN 10
#define NSEC 4
#define I2C_DEV_ADDR 0x54
#define NSINDIV 36

struct BLDC_4_00 b;
struct PIDcntrl p;

float spset = 120, stDCmax = 60, minspeedCW = 45,minspeedCCW = 80, maxDC = 1;
uint8 startpulse, rot, stamotor = 0, dir = 1, CTRLcmd = 1,sincmd = 0,sindrive = 0;
unsigned long prevmaintim,Maxcount,prevpwmtim,prevprintim = 0,randircnt = 0;
const unsigned pwmperiod = 1.0/PWMFREQ*1e6;
uint8 i2ccmd;
float i2cfloat, toberead;
uint8 i2cavail;
uint32_t i2c_cnt = 0;

void bin(unsigned n)
{
    unsigned i;
    for (i = 1 << 7; i > 0; i = i / 2)
        (n & i) ? printf("1") : printf("0");
}

/********************************************************************************************/

uint8 parseInp(char *c,float *val){
    static char str[10];
    uint8 cmdrcd = 0;
    static int i=0;char ch; 
    
    ch = UART_UartGetChar(); 
    if (ch){
        if(ch!='\n' && ch!='\r'){
            str[i] = ch;
            cmdrcd = 0;
            i++;
        }
        else{
            str[i] = 0; 
            i = 0;
            cmdrcd = 1;
        }
    }
    else
        return 0;
//    printf("Hello\n");
    if (cmdrcd){
        cmdrcd =0;
        *val = atof(str+1);
        *c = str[0];
        i = 0;
        //printf("%s == %d\n", str, (int)(val*1000));
        //printf("%c\n", str[0]);
        return 1;
    }
    return 0;
}
/********************************************************************************************/

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    float val=0;char ch;

    UART_Start();
    CTRL_Write(0);

    Counter_micros_Start();
    isr_millis_StartEx(isr_millis_Handler);
    
    BLDC_4_00_init(&b, 100, 0, 10000, NSEC*2);
    PIDcntrl_init(&p, 0);
    intptr = &b;
    
    //p.K = 0.1; p.Ti = 3; p.Td = 0.2;
    p.K = 0.003; p.Ti = 5; p.Td = 0.2;
    p.Tset = spset;
    unsigned long periodset = 1.0/p.Tset*60.0*1e6;
    Maxcount = periodset/4/(1.0/PWMFREQ*1e6);
    p.vmax = 90;//15;
    p.vmin = 0;//-15; 

    maxDC = 0;
    startpulse = 1;
    rot = 0;
    b.maxDC = p.vmax;
    startmotor(&b, 'A');
    stamotor = 0;
    printf("---------------------------------------\n");
    printf("Direction: ");printf((dir == 0)? "CCW\n":"CW\n");
    printf("PID K: "); printf("Multiplied by 1000: %d\n",(int)(p.K*1000));
    printf("PID Ki: "); printf("Multiplied by 1000: %d\n",(int)(p.Ti*1000));
    printf("PID Vmax: "); printf("%d\n",(int)p.vmax);
    printf("PID Vmin: "); printf("%d\n",(int)p.vmin);
    printf("Speed: "); printf("%d\n", (int)p.Tset);
    printf("Max PWM: "); printf("%d\n", (int)b.maxDC);  
    printf("Press A1 to start the motor\n");
    prevmaintim = Counter_micros_ReadCounter();
    
//    UART_UartPutString("Initialised\n");
    
    for(;;){
        static uint8 s,i, refstate = 1,sp_index = 0, randrot = 0;
        static uint8 ctrl = 1;
        static float T = 5, sp, sparray[FLEN], spfil = 0;
        static unsigned long period, sptime,spdelta, inttimdiff;
        static unsigned long secount, NRcount, NRcntupd = 0;
        static unsigned long angindex,sinprevtim=0,sincount;
        static float delta_act;
        
        if(parseInp(&ch,&val)){
            switch(ch){
                case 'M': maxDC = val; break; // PWM value
                case 'D': dir = (val<0)?0:1;break;
                case 'P': p.K = val;break;
                case 'I': p.Ti = val;break;
                case 'd': p.Td = val;break;
                case 'V': p.vmax = val;break;
                case 'S': spset = val;p.Tset += (val - p.Tset)/T;break;
                case 'K': minspeedCW = val;
                case 'B': minspeedCCW = val;
                case 'U': b.maxDC = val;break;
                case 'L': stDCmax = val;break;
                case 'T': T = fabs(val);break;
                case 'G': CTRLcmd = (uint8)(val);break;
                case 'r': reset(&p);break;
                case 'R': brake(&b);break;
                case 'A': stamotor = (val<0.5)?0:1;break;
                case 'N': sincmd = val;break;
                case 'O': printf("---------------------------------------\n");
                          printf("Direction: "); printf((dir == 0)? "CCW\n":"CW\n");
                          printf("PID K multiplied by 1000: "); printf("%d\n",(int)(p.K*1000));
                          printf("PID Ki multiplied by 1000: "); printf("%d\n",(int)(p.Ti*1000));
                          printf("PID Vmax multiplied by 1000: "); printf("%d\n",(int)(p.vmax*1000));
                          printf("PID Vmin multiplied by 1000: "); printf("%d\n",(int)(p.vmin*1000));
                          printf("Set speed multiplied by 1000: "); printf("%d\n",(int)(spset*1000));
                          printf("Present speed multiplied by 1000: "); printf("%d\n",(int)(spfil*1000));
                          printf("Max PWM: "); printf("%d\n", b.maxDC);
                          break;
                case 'C': printf("Status: ");
                          printf("%d (Multiplied by 1000)",(int)spset); printf(",");
                          printf("%d (Multiplied by 1000)",(int)spfil);printf(",");
                          printf("%d\n",rot);printf(",");
                          break;
            
            }
        }
        if (stamotor){
            s = getstate(&b);
//            printf("%d\n",s);
            if (isinttrig(&b)||startpulse){
//                printf("%d\n",startpulse);
                if (isinttrig(&b)){
                    startpulse = 0;
                    unsigned long delta;
                    delta = del_btn_int(&b);
                    period+= delta;
                    prevmaintim = Counter_micros_ReadCounter();
                    s = getstate(&b);
//                    printf("%x\n", s);
//                    bin(s);
//                    printf("\n");
                    if(refstate == s)
                        secount++;
                    NRcount = 0;
                    clrint(&b);
//                    printf("Inside stamotor and isinttrig(&b)\n");
//                    printf("secount: %lu\n", secount);
                }
            }
            if (secount == 4){
//                printf("Inside secount\n");
                secount = 0;
                rot = 1;NRcount = 0;
                randircnt = 0;
                sp = 1.0/period*1e6*60;
                sparray[sp_index] = sp;
                sp_index = (sp_index+1)%FLEN;
                spfil = 0;
                for (int c = 0; c<FLEN; c++)
                    spfil += sparray[c];
                spfil = spfil/FLEN;
                if ((fabs(p.Tset-spfil)/p.Tset*100) < 2){
                    p.Tset += (spset - p.Tset)/T; 
                    delta_act = 1.0/p.Tset*60*1e6/NSEC/6;
                }
                period = 0;
            }
            if ((Counter_micros_ReadCounter() - prevpwmtim) > 1000){
                prevpwmtim = Counter_micros_ReadCounter();
                float tempPID;
                if (ctrl){
                    maxDC = evalCntrl(&p,spfil,1e-3);
                    if (!rot)
                        s = getstate(&b);
                    maxDC = commute_trapz(&b,nextstate(&b,s,dir),maxDC);
                }
                else
                    reset(&p);
            }
            if ((Counter_micros_ReadCounter() - prevprintim) > 1000000){
                prevprintim = Counter_micros_ReadCounter();
                printf("%d ",dir);
                printf("%d ",(int)(maxDC));
                printf("%d ",(int)(p.Tset));
                printf("%d ", sindrive);
                printf("%d\n",(int)(spfil));
            }
            if ((Counter_micros_ReadCounter() - prevmaintim) > (60.0/p.Tset/4*1e6)){
                rot = 0;
                prevmaintim = Counter_micros_ReadCounter();
                NRcount++;
                startpulse = 1;
                spfil = 0;
            }
        }    
        else {
            brake(&b);
            maxDC = 0;
            spfil = 0;
        }
    }
}
        


//int main(void)
//{
//    CyGlobalIntEnable; /* Enable global interrupts. */
//    float val=0;char ch;
//
//    UART_Start();
//    CTRL_Write(0);
//
//    Counter_micros_Start();
//    isr_millis_StartEx(isr_millis_Handler);
//    
//    BLDC_4_00_init(&b, 100, 0, 5000, NSEC*2);
//    PIDcntrl_init(&p, 0);
//    intptr = &b;
//    
//    //p.K = 0.1; p.Ti = 3; p.Td = 0.2;
//    p.K = 0.03; p.Ti = 5; p.Td = 0.2;
//    p.Tset = spset;
//    unsigned long periodset = 1.0/p.Tset*60.0*1e6;
//    Maxcount = periodset/4/(1.0/PWMFREQ*1e6);
//    p.vmax = 90;//15;
//    p.vmin = 0;//-15; 
//
//    maxDC = 0;
//    startpulse = 1;
//    rot = 0;
//    b.maxDC = p.vmax;
//    startmotor(&b, 'A');
//    stamotor = 0;
//    printf("---------------------------------------\n");
//    printf("Direction: ");printf((dir == 0)? "CCW\n":"CW\n");
//    printf("PID K: "); printf("Multiplied by 1000: %d\n",(int)(p.K*1000));
//    printf("PID Ki: "); printf("Multiplied by 1000: %d\n",(int)(p.Ti*1000));
//    printf("PID Vmax: "); printf("%d\n",(int)p.vmax);
//    printf("PID Vmin: "); printf("%d\n",(int)p.vmin);
//    printf("Speed: "); printf("%d\n", (int)p.Tset);
//    printf("Max PWM: "); printf("%d\n", (int)b.maxDC);  
////    printf("Press A1 to start the motor\n");
//    prevmaintim = Counter_micros_ReadCounter();
//    
//    uint8 s=9;
//    
////    UART_UartPutString("Initialised\n");
//    
//    for(;;){
//        if(parseInp(&ch,&val))
//        {
//            switch(ch)
//            {
//                case 'C': commute_trapz(&b, val, 10);
//            }
//        }
//        
//        if(Counter_micros_ReadCounter() - prevmaintim > 1000000)
//        {
//            s = getstate(&b);
//            printf("Present State: %d\n", s);
//            prevmaintim = Counter_micros_ReadCounter();
//        }
//    }
//}



/* [] END OF FILE */



















































































//struct BLDC_4_00 proc1;
//int main(void)
//{
//    CyGlobalIntEnable; /* Enable global interrupts. */
//    
//    BLDC_4_00_init(&proc1, 100, 0, 10000, 8);
//    
//    UART_Start();
//    CTRL_Write(0);
//
//    uint8 state, set_state;
//    uint8 dc = 1;
//    float result;
//
//    for(;;)
//    {
////        set_state = UART_UartGetChar();       
////        if((set_state > 48) && (set_state < 56)){
////            result = commute_trapz(&proc1, set_state-48, dc);
////            printf("%d\n", (int)result);
////        }
//        
//        state = getstate(&proc1);
//        printf("%d\n", state);
//    }
//}