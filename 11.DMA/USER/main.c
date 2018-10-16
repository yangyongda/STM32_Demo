#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "dma.h" 
 
/************************************************
DMAʵ��

����TX DMA�� �ڴ�����ݷ��͵�����
DMA��������ʱ LED��Ȼ������ˮ����ʾ
************************************************/
#define SEND_BUF_SIZE 8200	//�������ݳ���

u8 SendBuff[SEND_BUF_SIZE];	//�������ݻ�����

int main(void)
{	
	int i;
	delay_init();	    //��ʱ������ʼ��
	uart_init(115200);	 	//���ڳ�ʼ��Ϊ115200
	LED_Init();		  	//��ʼ����LED���ӵ�Ӳ���ӿ�
	MYDMA_Config(DMA1_Channel4,(u32)&USART1->DR,(u32)SendBuff,SEND_BUF_SIZE);//DMA1ͨ��4,����Ϊ����1,�洢��ΪSendBuff,����SEND_BUF_SIZE.
	 
	for(i =0; i<SEND_BUF_SIZE ; i++)
	{
		SendBuff[i] = 0xff;
	}

	USART_DMACmd(USART1,USART_DMAReq_Tx,ENABLE); //ʹ�ܴ���1��DMA����      
	MYDMA_Enable(DMA1_Channel4);//��ʼһ��DMA���䣡	  
	
	while(1)
	{
		
		LED0=0;	//��
		LED1=1;	//��
		LED2=1;	//��
		delay_ms(300);	 //��ʱ300ms
		LED0=1;	//��
		LED1=0;	//��
		LED2=1;	//��
		delay_ms(300);	//��ʱ300ms
		LED0=1;	//��
		LED1=1;	//��
		LED2=0;	//��
		delay_ms(300);	//��ʱ300ms
	}
}




