#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "timer.h" 
 
/************************************************
定时器实验

定时器500ms进一次中断，将LED的状态取反(亮灭交替)
************************************************/


 int main(void)
 {	
	SCB->VTOR = FLASH_BASE | 0x10000; /* Vector Table Relocation in Internal FLASH. */
	 
	delay_init();	    //延时函数初始化	  
	LED_Init();		  	//初始化与LED连接的硬件接口
	//500ms
	TIM3_Int_Init(4999,7199);// 72000Khz/(7199+1)=10Khz的计数频率，计数到5000为500ms (1/10000*5000 = 0.5s = 500ms) 
	while(1)
	{
		delay_ms(300);	//延时300ms
	}
 }



