#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "key.h" 
#include "exti.h"
 
/************************************************
外部中断实验
按键产生中断
************************************************/


 int main(void)
 {	
	delay_init();	    //延时函数初始化	  
	LED_Init();		  	//初始化与LED连接的硬件接口
	KEY_Init();
	EXTIX_Init();
	
	//LED0=0;					//点亮LED0 
	while(1)
	{
		
	}
 }



