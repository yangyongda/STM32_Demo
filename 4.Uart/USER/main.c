#include "sys.h"
#include "delay.h"
#include "uart.h"

 
/************************************************
串口通信实验

************************************************/


 int main(void)
 {	
	delay_init();	    //延时函数初始化	  
	Uart_Init(); 	//初始化串口1
	 
	while(1)
	{
		printf("hello\r\n");
		delay_ms(500);
	}
 }



