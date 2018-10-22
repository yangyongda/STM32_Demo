#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "timer.h" 
 
/************************************************
��ʱ��ʵ��

��ʱ��500ms��һ���жϣ���LED��״̬ȡ��(������)
************************************************/


 int main(void)
 {	
	SCB->VTOR = FLASH_BASE | 0x10000; /* Vector Table Relocation in Internal FLASH. */
	 
	delay_init();	    //��ʱ������ʼ��	  
	LED_Init();		  	//��ʼ����LED���ӵ�Ӳ���ӿ�
	//500ms
	TIM3_Int_Init(4999,7199);// 72000Khz/(7199+1)=10Khz�ļ���Ƶ�ʣ�������5000Ϊ500ms (1/10000*5000 = 0.5s = 500ms) 
	while(1)
	{
		delay_ms(300);	//��ʱ300ms
	}
 }



