#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "stmflash.h"
 
/************************************************
�ڲ�Flashʵ��

��д�ڲ�Flash
************************************************/

//Ҫд�뵽STM32 FLASH���ַ�������
const u8 TEXT_Buffer[]={"STM32F103 FLASH TEST"};
#define SIZE sizeof(TEXT_Buffer)		//���鳤��
#define FLASH_SAVE_ADDR  0X08070000		//����FLASH �����ַ(����Ϊż��������ֵҪ���ڱ�������ռ��FLASH�Ĵ�С+0X08000000)


int main(void)
{
	u8 datatemp[SIZE];	 
	delay_init();	    //��ʱ������ʼ��	
	uart_init(115200);

	STMFLASH_Write(FLASH_SAVE_ADDR,(u16*)TEXT_Buffer,SIZE);
	delay_ms(1000);
	STMFLASH_Read(FLASH_SAVE_ADDR,(u16*)datatemp,SIZE);
	 
	while(1)
	{
		printf("%s\r\n", datatemp);
		delay_ms(1000);
	}
}

