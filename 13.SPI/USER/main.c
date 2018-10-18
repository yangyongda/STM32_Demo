#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "SST25VF016B.h"
 
 
/************************************************
SPI实验

通过spi接口读写外部Flash(SST25VF016B)
************************************************/

const u8 TEXT_Buffer[]={"WarShipSTM32 SPI TEST"};
#define SIZE sizeof(TEXT_Buffer)
	
int main(void)
{	
	u8 datatemp[SIZE];
	
	delay_init();	    //延时函数初始化	  
	SST25VF16B_Init();
	
	Section_Write(0, (u8*)TEXT_Buffer, SIZE);
	delay_ms(1000);
	Section_Read(0, datatemp, SIZE);
	
	while(1)
	{
		printf("%s\r\n", datatemp);
		delay_ms(1000);
	}
}




