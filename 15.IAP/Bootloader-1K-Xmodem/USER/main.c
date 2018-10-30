#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "stmflash.h"
#include "key.h"
#include "exti.h"
#include "iap.h"
#include "xmodem.h"
 
/************************************************
IAP实验

bootloader程序
************************************************/




int main(void)
{	 
	delay_init();	    //延时函数初始化	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置NVIC中断分组2:2位抢占优先级，2位响应优先级 
	KEY_Init();
	EXTIX_Init();
	uart_init(115200);	//串口初始化为115200
	TIM3_Int_Init(9999, 7199);
	
	
	while(1)
	{
		if(updateFlag == 1)
		{
			updateFlag = 0;
			xmodemReceive(2);
		}
		
		if(gotoApp == 1)
		{
			
			printf("开始执行FLASH用户代码!!\r\n");
			if(((*(vu32*)(FLASH_APP1_ADDR+4))&0xFF000000)==0x08000000)//判断是否为0X08XXXXXX.
			{	 
				iap_load_app(FLASH_APP1_ADDR);//执行FLASH APP代码
			}
			else 
			{
				printf("非FLASH应用程序,无法执行!\r\n");
			}	
			
		}
	}
}

