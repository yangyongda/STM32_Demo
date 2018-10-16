#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "timer.h" 
 
/************************************************
定时器捕获实验

对脉冲进行捕获计数
************************************************/
#define PULSE PBout(7) // PB7  引脚模拟脉冲波

extern int count;

void pulse_init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;	//GPIO配置结构体

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //使能PB端口时钟

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;				 			//PB.7 端口配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	GPIO_Init(GPIOB, &GPIO_InitStructure);					 			//根据设定参数初始化GPIOB.7
	GPIO_SetBits(GPIOB,GPIO_Pin_7);						 					//PB.7 输出高
}

int main(void)
{	
	delay_init();	    //延时函数初始化	  
	pulse_init();
	uart_init(115200);
	TIM5_Cap_Init(0XFFFF,72-1); //以1Mhz的频率计数 
	
	while(1)
	{
		PULSE = 0;
		delay_ms(10);
		PULSE = 1;
		delay_ms(20);
		
		printf("count = %d \r\n", count);
	}
}



