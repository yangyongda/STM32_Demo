#include "exti.h"
#include "led.h"
#include "delay.h"
#include "usart.h"
#include "key.h"

//�ⲿ�ж�5�������
void EXTIX_Init(void)
{
 
	EXTI_InitTypeDef EXTI_InitStructure;	//�ⲿ�ж�����
	NVIC_InitTypeDef NVIC_InitStructure;	//�жϿ���������

	//AFIOʱ�ӣ�GPIO�˿ڸ��ù���ʱ�ӣ���ʹ��GPIO�˿ڵĸ��ù���ʱҪ������ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOC ,ENABLE);	//ʹ�ܸ��ù���ʱ��

	//GPIOC.5 �ж����Լ��жϳ�ʼ������   �½��ش���
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource5);

	EXTI_InitStructure.EXTI_Line=EXTI_Line5;	//KEY1
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;	//�½���
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);	 	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���

	//���ж���ж�(���������жϵ�)ʱ��һ��ֻ����һ�����ȼ�����
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 				//����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;			//ʹ�ܰ���1���ڵ��ⲿ�ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//��ռ���ȼ�2�� 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x03;					//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
	NVIC_Init(&NVIC_InitStructure); 
 
}

//�ⲿ�ж�5������� 
void EXTI9_5_IRQHandler(void)
{
	
	delay_ms(10);//����
	if(KEY1 == 0)
	{
		LED0 = !LED0;
	}
	EXTI_ClearITPendingBit(EXTI_Line5);  //���LINE5�ϵ��жϱ�־λ  
	
}
 

 