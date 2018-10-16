#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "key.h" 
#include "exti.h"
#include "wdg.h"
 
/************************************************
�������Ź�ʵ��


ϵͳ������ƻ�����һ����Ϩ��
û�������Ļ��ƻ�һֱ��

��һ�°������ж�ι��
���û��ι����1s��ϵͳ������
************************************************/


 int main(void)
 {	
	delay_init();	    //��ʱ������ʼ��	  
	LED_Init();		  	//��ʼ����LED���ӵ�Ӳ���ӿ�
	KEY_Init();
	EXTIX_Init();
	IWDG_Init(4,625);    //���Ƶ��Ϊ64,����ֵΪ625,���ʱ��Ϊ1s
	
	LED0=0;					//����LED0
	delay_ms(400);	 
	while(1)
	{
		LED0 = 1;
		delay_ms(50);
	}
 }



