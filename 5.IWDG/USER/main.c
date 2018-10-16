#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "key.h" 
#include "exti.h"
#include "wdg.h"
 
/************************************************
独立看门狗实验


系统重启后灯会先亮一下再熄灭
没有重启的话灯会一直灭

按一下按键进中断喂狗
如果没有喂狗，1s后系统会重启
************************************************/


 int main(void)
 {	
	delay_init();	    //延时函数初始化	  
	LED_Init();		  	//初始化与LED连接的硬件接口
	KEY_Init();
	EXTIX_Init();
	IWDG_Init(4,625);    //与分频数为64,重载值为625,溢出时间为1s
	
	LED0=0;					//点亮LED0
	delay_ms(400);	 
	while(1)
	{
		LED0 = 1;
		delay_ms(50);
	}
 }



