#include "exti.h"
#include "delay.h"
#include "usart.h"
#include "key.h"

u8 updateFlag = 0; //更新标志位
u8 gotoApp = 0;

//外部中断5服务程序
void EXTIX_Init(void)
{
 
	EXTI_InitTypeDef EXTI_InitStructure;	//外部中断配置
	NVIC_InitTypeDef NVIC_InitStructure;	//中断控制器配置

	//AFIO时钟：GPIO端口复用功能时钟，当使用GPIO端口的复用功能时要开启该时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOC ,ENABLE);	//使能复用功能时钟

	//GPIOC.5 中断线以及中断初始化配置   下降沿触发
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource5);

	EXTI_InitStructure.EXTI_Line=EXTI_Line5;	//KEY1
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;	//下降沿
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);	 	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器
	
	//GPIOC.1 中断线以及中断初始化配置   下降沿触发
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource1);
	EXTI_InitStructure.EXTI_Line=EXTI_Line1;	//KEY2
	EXTI_Init(&EXTI_InitStructure);

	//当有多个中断(包括串口中断等)时，一般只配置一次优先级分组
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 				//设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;			//使能按键1所在的外部中断通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级2， 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x03;					//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
	NVIC_Init(&NVIC_InitStructure); 
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;			//使能按键2所在的外部中断通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x03;	//抢占优先级3， 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x03;					//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
	NVIC_Init(&NVIC_InitStructure); 
 
}

//外部中断5服务程序 
void EXTI9_5_IRQHandler(void)
{
	
	delay_ms(10);//消抖
	if(KEY1 == 0)
	{
		updateFlag = 1;	//开始更新
	}
	EXTI_ClearITPendingBit(EXTI_Line5);  //清除LINE5上的中断标志位  
	
}
 
//外部中断1服务程序 
void EXTI1_IRQHandler(void)
{
	
	delay_ms(10);//消抖
	if(KEY2 == 0)
	{
		gotoApp = 1;	//开始更新
	}
	EXTI_ClearITPendingBit(EXTI_Line1);  //清除LINE1上的中断标志位  
	
}

 
