#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "key.h" 
 
/************************************************
Keyʵ��
GPIO����
************************************************/


 int main(void)
 {	
	delay_init();	    //��ʱ������ʼ��	  
	LED_Init();		  	//��ʼ����LED���ӵ�Ӳ���ӿ�
	KEY_Init();
	while(1)
	{
		LED1 = 1;	//��
		LED2 = 1;
		
		if(KEY1 == 0)	//����
		{
			delay_ms(10);	//����
			if(KEY1 == 0)
			{
				LED1 = 0; //��
				while(KEY1 == 0); //�ȴ��ͷ�
			}
		}
		
		if(KEY2 == 0)	//����
		{
			delay_ms(10);	//����
			if(KEY2 == 0)
			{
				LED2 = 0; //��
				while(KEY2 == 0); //�ȴ��ͷ�
			}
		}
	}
 }



