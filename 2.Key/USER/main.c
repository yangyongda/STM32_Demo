#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "key.h" 
 
/************************************************
Key实验
GPIO输入
************************************************/


 int main(void)
 {	
	delay_init();	    //延时函数初始化	  
	LED_Init();		  	//初始化与LED连接的硬件接口
	KEY_Init();
	while(1)
	{
		LED1 = 1;	//灭
		LED2 = 1;
		
		if(KEY1 == 0)	//按下
		{
			delay_ms(10);	//消抖
			if(KEY1 == 0)
			{
				LED1 = 0; //亮
				while(KEY1 == 0); //等待释放
			}
		}
		
		if(KEY2 == 0)	//按下
		{
			delay_ms(10);	//消抖
			if(KEY2 == 0)
			{
				LED2 = 0; //亮
				while(KEY2 == 0); //等待释放
			}
		}
	}
 }



