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

void DisableOtherDevice(void)
{
	GPIO_InitTypeDef   	GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	
	//触摸屏也使用SPI通信的引脚，所以要禁用这些器件，防止它们的干扰
	//禁止触摸屏片选
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Init(GPIOC,&GPIO_InitStructure);
	
	//禁止触摸屏片选
	GPIO_SetBits(GPIOC,GPIO_Pin_4);
}

int main(void)
{	
	u8 datatemp[SIZE];
	
	delay_init();	    //延时函数初始化	
	uart_init(115200);
	DisableOtherDevice(); //其他设备使用SPI1，所以要将其他设备的片选禁用
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




