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
	u16 led0pwmval=0;
	u8 dir=1;	
	delay_init();	    //延时函数初始化	  
	LED_Init();		  	//初始化与LED连接的硬件接口
	TIM3_PWM_Init(899,0);	 //不分频。PWM频率=72000000/900=80Khz 
	while(1)
	{
		delay_ms(10);	 
		if(dir)led0pwmval++;
		else led0pwmval--;

 		if(led0pwmval>300)dir=0;
		if(led0pwmval==0)dir=1;										 
		TIM_SetCompare2(TIM3,led0pwmval);		
	}
}



