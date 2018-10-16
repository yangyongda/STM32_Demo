#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "dma.h" 
 
/************************************************
DMA实验

串口TX DMA， 内存的数据发送到串口
DMA发送数据时 LED依然进行流水灯显示
************************************************/
#define SEND_BUF_SIZE 8200	//发送数据长度

u8 SendBuff[SEND_BUF_SIZE];	//发送数据缓冲区

int main(void)
{	
	int i;
	delay_init();	    //延时函数初始化
	uart_init(115200);	 	//串口初始化为115200
	LED_Init();		  	//初始化与LED连接的硬件接口
	MYDMA_Config(DMA1_Channel4,(u32)&USART1->DR,(u32)SendBuff,SEND_BUF_SIZE);//DMA1通道4,外设为串口1,存储器为SendBuff,长度SEND_BUF_SIZE.
	 
	for(i =0; i<SEND_BUF_SIZE ; i++)
	{
		SendBuff[i] = 0xff;
	}

	USART_DMACmd(USART1,USART_DMAReq_Tx,ENABLE); //使能串口1的DMA发送      
	MYDMA_Enable(DMA1_Channel4);//开始一次DMA传输！	  
	
	while(1)
	{
		
		LED0=0;	//亮
		LED1=1;	//灭
		LED2=1;	//灭
		delay_ms(300);	 //延时300ms
		LED0=1;	//灭
		LED1=0;	//亮
		LED2=1;	//灭
		delay_ms(300);	//延时300ms
		LED0=1;	//灭
		LED1=1;	//灭
		LED2=0;	//亮
		delay_ms(300);	//延时300ms
	}
}




