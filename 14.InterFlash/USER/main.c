#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "stmflash.h"
 
/************************************************
内部Flash实验

读写内部Flash
************************************************/

//要写入到STM32 FLASH的字符串数组
const u8 TEXT_Buffer[]={"STM32F103 FLASH TEST"};
#define SIZE sizeof(TEXT_Buffer)		//数组长度
#define FLASH_SAVE_ADDR  0X08070000		//设置FLASH 保存地址(必须为偶数，且其值要大于本代码所占用FLASH的大小+0X08000000)


int main(void)
{
	u8 datatemp[SIZE];	 
	delay_init();	    //延时函数初始化	
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

