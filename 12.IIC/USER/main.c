#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "24cxx.h"
 
 
/************************************************
I2C实验

读写IIC接口的EEPROM(AT24C02)
************************************************/


//要写入到24c02的字符串数组
const u8 TEXT_Buffer[]={"WarShipSTM32 IIC TEST"};
#define SIZE sizeof(TEXT_Buffer)	
	
int main(void)
{	
	u8 datatemp[SIZE];
	
	delay_init();	    //延时函数初始化	  
	uart_init(115200);	 	//串口初始化为115200
	AT24CXX_Init();			//IIC初始化 
	
	//写进EEPROM
	AT24CXX_Write(0,(u8*)TEXT_Buffer,SIZE);
	
	delay_ms(1000);
	
	AT24CXX_Read(0,datatemp,SIZE);
	while(1)
	{
		printf("%s", datatemp);
		delay_ms(1000);
	}
}


