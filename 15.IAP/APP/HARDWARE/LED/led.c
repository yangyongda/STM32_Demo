#include "led.h"


//��ʼ��PB5��PE5Ϊ�����.��ʹ���������ڵ�ʱ��		    
//LED IO��ʼ��
void LED_Init(void)
{
 
	GPIO_InitTypeDef  GPIO_InitStructure;	//GPIO���ýṹ��

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOD, ENABLE);	 //ʹ��PB,PD�˿�ʱ��

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;				 			//LED0-->PB.5 �˿�����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
	GPIO_Init(GPIOB, &GPIO_InitStructure);					 			//�����趨������ʼ��GPIOB.5
	GPIO_SetBits(GPIOB,GPIO_Pin_5);						 					//PB.5 �����

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;	    		 //LED1-->PD.6 �˿�����, �������
	GPIO_Init(GPIOD, &GPIO_InitStructure);	  				 	//������� ��IO���ٶ�Ϊ50MHz�� �ṹ��ĳ�Ա�����Ѿ���ʼ���ˣ����Դ˴�����д
	GPIO_SetBits(GPIOD,GPIO_Pin_6); 						 				//PD.6 ����� 

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;	    		 //LED1-->PD.3 �˿�����, �������
	GPIO_Init(GPIOD, &GPIO_InitStructure);	  				 	//������� ��IO���ٶ�Ϊ50MHz�� �ṹ��ĳ�Ա�����Ѿ���ʼ���ˣ����Դ˴�����д
	GPIO_SetBits(GPIOD,GPIO_Pin_3); 						 				//PD.3 ����� 
}
 
