#include "sys.h"
#include "delay.h"
#include "uart.h"
#include "ESP8266.h"
 
/************************************************
ESP8266ʵ��

************************************************/



 int main(void)
 {	
	delay_init();	    //��ʱ������ʼ��	  
	Uart1_Init(); 	//��ʼ������1
	initEsp8266(SSID, PASSWORD);
	//STA_UDP_Mode();
	//STA_TCP_Server();
	 STA_TCP_Client();	//Ҫ��֤����������
	 
	while(1)
	{
		
		delay_ms(500);
		//UDP
		//Uart2_Send_Buffer((u8*)"ssss",5);
		
		//TCP Server
		//sendData(TCP_SERVER, 0,5);
		//delay_ms(500);
		//Uart2_Send_Buffer((u8*)"ssss",5);
		
		//TCP Client
		Uart2_Send_Buffer((u8*)"ssss",5);
	}
 }



