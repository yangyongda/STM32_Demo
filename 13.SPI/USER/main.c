#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "SST25VF016B.h"
 
 
/************************************************
SPIʵ��

ͨ��spi�ӿڶ�д�ⲿFlash(SST25VF016B)
************************************************/

const u8 TEXT_Buffer[]={"WarShipSTM32 SPI TEST"};
#define SIZE sizeof(TEXT_Buffer)

void DisableOtherDevice(void)
{
	GPIO_InitTypeDef   	GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	
	//������Ҳʹ��SPIͨ�ŵ����ţ�����Ҫ������Щ��������ֹ���ǵĸ���
	//��ֹ������Ƭѡ
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Init(GPIOC,&GPIO_InitStructure);
	
	//��ֹ������Ƭѡ
	GPIO_SetBits(GPIOC,GPIO_Pin_4);
}

int main(void)
{	
	u8 datatemp[SIZE];
	
	delay_init();	    //��ʱ������ʼ��	
	uart_init(115200);
	DisableOtherDevice(); //�����豸ʹ��SPI1������Ҫ�������豸��Ƭѡ����
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




