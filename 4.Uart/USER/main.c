#include "sys.h"
#include "delay.h"
#include "uart.h"

 
/************************************************
����ͨ��ʵ��

************************************************/


 int main(void)
 {	
	delay_init();	    //��ʱ������ʼ��	  
	Uart_Init(); 	//��ʼ������1
	 
	while(1)
	{
		printf("hello\r\n");
		delay_ms(500);
	}
 }



