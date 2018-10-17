#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "24cxx.h"
 
 
/************************************************
I2Cʵ��

��дIIC�ӿڵ�EEPROM(AT24C02)
************************************************/


//Ҫд�뵽24c02���ַ�������
const u8 TEXT_Buffer[]={"WarShipSTM32 IIC TEST"};
#define SIZE sizeof(TEXT_Buffer)	
	
int main(void)
{	
	u8 datatemp[SIZE];
	
	delay_init();	    //��ʱ������ʼ��	  
	uart_init(115200);	 	//���ڳ�ʼ��Ϊ115200
	AT24CXX_Init();			//IIC��ʼ�� 
	
	//д��EEPROM
	AT24CXX_Write(0,(u8*)TEXT_Buffer,SIZE);
	
	delay_ms(1000);
	
	AT24CXX_Read(0,datatemp,SIZE);
	while(1)
	{
		printf("%s", datatemp);
		delay_ms(1000);
	}
}


