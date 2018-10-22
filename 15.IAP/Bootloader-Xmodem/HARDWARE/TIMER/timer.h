#ifndef __TIMER_H
#define __TIMER_H
#include "sys.h"
#include "xmodem.h"


void TIM3_Int_Init(u16 arr,u16 psc);
void TIM3_Stop(void);
void TIM3_Start(u16 arr);
 
#endif
