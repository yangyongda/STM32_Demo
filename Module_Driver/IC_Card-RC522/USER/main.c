#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "rc522.h"
 
 
/************************************************
RC522驱动实验

通过spi接口
************************************************/

u8 KEY[6]={0xff,0xff,0xff,0xff,0xff,0xff};
u8 readBuf[16];
u8 writeBuf[16]={0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0F};

int main(void)
{	
	u8 i;
	u8 Temp[4], UID[5];
	delay_init();	    //延时函数初始化	
	uart_init(115200);
	
	RC522_Init();
	PcdReset();
	PcdAntennaOff(); 
	PcdAntennaOn();  
	
	//printf("111");
	while(1)
	{
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
			
			if(PcdAnticoll(UID)==MI_OK)
			{ 
				printf("Card Id is:%x%x%x%x\r\n", UID[0],UID[1],UID[2],UID[3]);
				
				if(PcdSelect(UID) == MI_OK)
				{
					printf("select card success\r\n");
					if(PcdAuthState(0x60,0x09,KEY,UID) == MI_OK)
					{
						printf("auth pass\r\n");
						if(PcdRead(0x09, readBuf) == MI_OK)
						{
							for(i = 0; i < 16; i++)
								printf("%x", readBuf[i]);
						}
						
						if(PcdWrite(0x09, writeBuf) == MI_OK)
						{
							if(PcdRead(0x09, readBuf) == MI_OK)
							{
								for(i = 0; i < 16; i++)
									printf("%x", readBuf[i]);
							}
						}
					}
				}
			}
			

		}
		
		delay_ms(1000);
		

	}
}




