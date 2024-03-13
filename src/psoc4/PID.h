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
#ifndef PID_H
#define PID_H
    
#include "stdio.h"
    
struct PIDcntrl{
    float Tprev,P,I,D;
    float K,Ti,Td, Tw, b, N;
    float Tset,vmax, vmin;
    unsigned upInt;
};

void PIDcntrl_init(struct PIDcntrl *p, float Tset){
    p->K = 0.1;
    p->Ti = 100;
    p->Td = 0;
    p->Tw = 100;
    p->b = 1;
    p->N = 20;
    p->vmax = 1;
    p->vmin = -1;
    p->upInt = 0;
    
    p->Tset = Tset;
    p->Tprev = 0;
    p->P = 0;
    p->I = 0;
    p->D = 0;
}

float evalCntrl(struct PIDcntrl *p, float T, float h){
    float e,v,vout,os;
    p->P = (p->K)*((p->b)*(p->Tset)-T);
    e = p->Tset - T;
    p->I += (p->K)*h/(p->Ti)*e;
    p->D = p->Td/((p->Td)+(p->N)*h)*((p->D)-(p->K)*(p->N)*(T-(p->Tprev)));
    v = (p->P)+(p->I)+(p->D);
    vout = v;
    if (vout > p->vmax)
    vout = p->vmax;
    if (vout < p->vmin)
    vout = p->vmin;
    os = vout - v;
    p->I += h/(p->Tw)*os;
    p->Tprev = T;
    return vout;
}

void print(struct PIDcntrl *p){
    printf("P Multiplied by 100000:%d ", (int)p->P*100000);
    printf("I Multiplied by 100000:%d ", (int)p->I*100000);
    printf("D Multiplied by 100000:%d\n", (int)p->D*100000);
}

void reset(struct PIDcntrl *p){
    p->P = 0;
    p->I = 0;
    p->D = 0;
}

#endif
/* [] END OF FILE */
