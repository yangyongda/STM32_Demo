#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "stmflash.h"
#include "key.h"
#include "exti.h"
#include "iap.h"
#include "xmodem.h"
 
/************************************************
IAPʵ��

bootloader����
************************************************/




int main(void)
{	 
	delay_init();	    //��ʱ������ʼ��	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ� 
	KEY_Init();
	EXTIX_Init();
	uart_init(115200);	//���ڳ�ʼ��Ϊ115200
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

