#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "stmflash.h"
#include "key.h"
#include "exti.h"
#include "iap.h"
 
/************************************************
IAP实验

bootloader程序
************************************************/




int main(void)
{	 
	u16 oldcount=0;				//老的串口接收数据值
	u16 applenth=0;				//接收到的app代码长度
	u8 datatemp[10];
	
	delay_init();	    //延时函数初始化	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置NVIC中断分组2:2位抢占优先级，2位响应优先级 
	KEY_Init();
	EXTIX_Init();
	uart_init(115200);	//串口初始化为115200
	
	while(1)
	{
		if(USART_RX_CNT)
		{
			if(oldcount==USART_RX_CNT)//新周期内,没有收到任何数据,认为本次数据接收完成.
			{
				applenth=USART_RX_CNT;
				oldcount=0;
				USART_RX_CNT=0;
				printf("用户程序接收完成!\r\n");
				printf("代码长度:%dBytes\r\n",applenth);
			}else 
				oldcount=USART_RX_CNT;
		}
		
		delay_ms(10);
		
		if(updateFlag == 1)
		{
			updateFlag = 0;	//清除更新标志位
			printf("开始更新固件...\r\n");	
			iap_write_appbin(FLASH_APP1_ADDR,USART_RX_BUF,applenth);//更新FLASH代码   
			printf("固件更新完成!\r\n");
			
			
			//更新结束后跳到app进行执行
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
		
		if(gotoApp == 1)
		{
			gotoApp = 0;
			//更新结束后跳到app进行执行
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

