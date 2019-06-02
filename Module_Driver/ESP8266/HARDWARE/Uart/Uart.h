#ifndef __UART_H
#define __UART_H
#include "stm32f10x.h"
#include "stdio.h"

void Uart1_Init(void);
void Uart2_Init(void);
u16 Uart2_Send_Buffer(u8 * bytes, u16 num);


#endif


