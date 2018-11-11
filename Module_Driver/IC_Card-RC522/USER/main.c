#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "rc522.h"
 
 
/************************************************
RC522����ʵ��

ͨ��spi�ӿ�

ע��: ��Ҫ��SPI��ͨ�����ʵ���̫�ߣ��ᵼ����ʱ��ͨ�Ų���

���������ǲ���д�ģ����Բ鿴�ĵ���ȷ��
************************************************/

u8 KEY[6]={0xff,0xff,0xff,0xff,0xff,0xff};	//Ĭ����Կ
u8 readBuf[16];
u8 writeBuf[16]={0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0D};

//M1����ĳһ��дΪ���¸�ʽ����ÿ�ΪǮ�����ɽ��տۿ�ͳ�ֵ����
//4�ֽڽ����ֽ���ǰ����4�ֽڽ��ȡ����4�ֽڽ�1�ֽڿ��ַ��1�ֽڿ��ַȡ����1�ֽڿ��ַ��1�ֽڿ��ַȡ�� 
u8 data1[16] = {0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0x02,0xFD,0x02,0xFD};
u8 addValue[4] = {100,0,0,0};	//��ֵ��ֵ
u8 subValue[4] = {10,0,0,0};	//�ۿ���ֵ

int main(void)
{	
	u8 i;
	u8 Temp[4], UID[5];
	delay_init();	    //��ʱ������ʼ��	
	uart_init(115200);
	
	RC522_Init();
	PcdReset();
	PcdAntennaOff(); 
	PcdAntennaOn();  
	
	//printf("111");
	while(1)
	{
		//Ѱ��
		if(PcdRequest(0x52,Temp)==MI_OK)
		{
			if(Temp[0]==0x04&&Temp[1]==0x00)  
				printf("MFOne-S50\r\n");
			else if(Temp[0]==0x02&&Temp[1]==0x00)
				printf("MFOne-S70\r\n");
			else if(Temp[0]==0x44&&Temp[1]==0x00)
				printf("MF-UltraLight\r\n");
			else if(Temp[0]==0x08&&Temp[1]==0x00)
				printf("MF-Pro\r\n");
			else if(Temp[0]==0x44&&Temp[1]==0x03)
				printf("MF Desire\r\n");
			else
				printf("Unknown\r\n");
			//����ײ
			if(PcdAnticoll(UID)==MI_OK)
			{ 
				printf("Card Id is:%x%x%x%x\r\n", UID[0],UID[1],UID[2],UID[3]);
				//ѡ��
				if(PcdSelect(UID) == MI_OK)
				{
					printf("select card success\r\n");
					//��д��
					if(PcdAuthState(0x60,0x09,KEY,UID) == MI_OK)	//��֤
					{
						printf("auth pass\r\n");
						if(PcdRead(0x09, readBuf) == MI_OK)	//������ֵ
						{
							printf("old value = ");
							for(i = 0; i < 16; i++)
								printf("%x", readBuf[i]);
							printf("\r\n");
						}
						
						if(PcdWrite(0x09, writeBuf) == MI_OK)	//д����ֵ
						{
							printf("write ok\r\n");
							if(PcdRead(0x09, readBuf) == MI_OK)	//����д���ֵ
							{
								printf("new value = ");
								for(i = 0; i < 16; i++)
									printf("%x", readBuf[i]);
								printf("\r\n");
							}
						}
					}
					
					printf("-----------------------------------------\r\n");
					//�Ӽ�ֵ
					if(PcdAuthState(0x60,0x02,KEY,UID) == MI_OK)	//��֤
					{
						printf("auth pass\r\n");
						if(PcdWrite(0x02, data1) == MI_OK)	//Ҫ��ĳ����Ǯ�����ܽ��ճ�ֵ�Ϳۿ�����
						{
							printf("write ok\r\n");
							if(PcdValue(0xC1, 0x02, addValue) == MI_OK)	//��ֵ
							{
								printf("recharge success\r\n");
								if(PcdRead(0x02, readBuf) == MI_OK)
								{
									printf("recharge after new value = ");
									for(i = 0; i < 4; i++)
										printf("%x", readBuf[i]);
									printf("\r\n");
								}
							}
							
							if(PcdValue(0xC0, 0x02, subValue) == MI_OK)	//�ۿ�
							{
								printf("charge success\r\n");
								if(PcdRead(0x02, readBuf) == MI_OK)
								{
									printf("charge after new value = ");
									for(i = 0; i < 4; i++)
										printf("%x", readBuf[i]);
									printf("\r\n");
								}
							}
						}
					}
					
				}
			}
			

		}
		
		delay_ms(1000);
		

	}
}




