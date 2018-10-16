#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "timer.h" 
 
/************************************************
��ʱ������ʵ��

��������в������
************************************************/
#define PULSE PBout(7) // PB7  ����ģ�����岨

extern int count;

void pulse_init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;	//GPIO���ýṹ��

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //ʹ��PB�˿�ʱ��

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;				 			//PB.7 �˿�����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
	GPIO_Init(GPIOB, &GPIO_InitStructure);					 			//�����趨������ʼ��GPIOB.7
	GPIO_SetBits(GPIOB,GPIO_Pin_7);						 					//PB.7 �����
}

int main(void)
{	
	delay_init();	    //��ʱ������ʼ��	  
	pulse_init();
	uart_init(115200);
	TIM5_Cap_Init(0XFFFF,72-1); //��1Mhz��Ƶ�ʼ��� 
	
	while(1)
	{
		PULSE = 0;
		delay_ms(10);
		PULSE = 1;
		delay_ms(20);
		
		printf("count = %d \r\n", count);
	}
}



