#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "key.h" 
#include "exti.h"
 
/************************************************
�ⲿ�ж�ʵ��
���������ж�
************************************************/


 int main(void)
 {	
	delay_init();	    //��ʱ������ʼ��	  
	LED_Init();		  	//��ʼ����LED���ӵ�Ӳ���ӿ�
	KEY_Init();
	EXTIX_Init();
	
	//LED0=0;					//����LED0 
	while(1)
	{
		
	}
 }



