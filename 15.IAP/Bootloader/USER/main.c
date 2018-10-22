#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "stmflash.h"
#include "key.h"
#include "exti.h"
#include "iap.h"
 
/************************************************
IAPʵ��

bootloader����
************************************************/




int main(void)
{	 
	u16 oldcount=0;				//�ϵĴ��ڽ�������ֵ
	u16 applenth=0;				//���յ���app���볤��
	u8 datatemp[10];
	
	delay_init();	    //��ʱ������ʼ��	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ� 
	KEY_Init();
	EXTIX_Init();
	uart_init(115200);	//���ڳ�ʼ��Ϊ115200
	
	while(1)
	{
		if(USART_RX_CNT)
		{
			if(oldcount==USART_RX_CNT)//��������,û���յ��κ�����,��Ϊ�������ݽ������.
			{
				applenth=USART_RX_CNT;
				oldcount=0;
				USART_RX_CNT=0;
				printf("�û�����������!\r\n");
				printf("���볤��:%dBytes\r\n",applenth);
			}else 
				oldcount=USART_RX_CNT;
		}
		
		delay_ms(10);
		
		if(updateFlag == 1)
		{
			updateFlag = 0;	//������±�־λ
			printf("��ʼ���¹̼�...\r\n");	
			iap_write_appbin(FLASH_APP1_ADDR,USART_RX_BUF,applenth);//����FLASH����   
			printf("�̼��������!\r\n");
			
			
			//���½���������app����ִ��
			printf("��ʼִ��FLASH�û�����!!\r\n");
			if(((*(vu32*)(FLASH_APP1_ADDR+4))&0xFF000000)==0x08000000)//�ж��Ƿ�Ϊ0X08XXXXXX.
			{	 
				iap_load_app(FLASH_APP1_ADDR);//ִ��FLASH APP����
			}
			else 
			{
				printf("��FLASHӦ�ó���,�޷�ִ��!\r\n");
			}		
		}
		
		if(gotoApp == 1)
		{
			gotoApp = 0;
			//���½���������app����ִ��
			printf("��ʼִ��FLASH�û�����!!\r\n");
			if(((*(vu32*)(FLASH_APP1_ADDR+4))&0xFF000000)==0x08000000)//�ж��Ƿ�Ϊ0X08XXXXXX.
			{	 
				iap_load_app(FLASH_APP1_ADDR);//ִ��FLASH APP����
			}
			else 
			{
				printf("��FLASHӦ�ó���,�޷�ִ��!\r\n");
			}		
		}
	}
}

