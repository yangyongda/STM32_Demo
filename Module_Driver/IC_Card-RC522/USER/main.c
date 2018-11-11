#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "rc522.h"
 
 
/************************************************
RC522驱动实验

通过spi接口

注意: 不要把SPI的通信速率调得太高，会导致有时候通信不上

部分扇区是不能写的，可以查看文档来确定
************************************************/

u8 KEY[6]={0xff,0xff,0xff,0xff,0xff,0xff};	//默认密钥
u8 readBuf[16];
u8 writeBuf[16]={0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0D};

//M1卡的某一块写为如下格式，则该块为钱包，可接收扣款和充值命令
//4字节金额（低字节在前）＋4字节金额取反＋4字节金额＋1字节块地址＋1字节块地址取反＋1字节块地址＋1字节块地址取反 
u8 data1[16] = {0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0x02,0xFD,0x02,0xFD};
u8 addValue[4] = {100,0,0,0};	//充值数值
u8 subValue[4] = {10,0,0,0};	//扣款数值

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
		//寻卡
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
			//防冲撞
			if(PcdAnticoll(UID)==MI_OK)
			{ 
				printf("Card Id is:%x%x%x%x\r\n", UID[0],UID[1],UID[2],UID[3]);
				//选卡
				if(PcdSelect(UID) == MI_OK)
				{
					printf("select card success\r\n");
					//读写块
					if(PcdAuthState(0x60,0x09,KEY,UID) == MI_OK)	//验证
					{
						printf("auth pass\r\n");
						if(PcdRead(0x09, readBuf) == MI_OK)	//读出旧值
						{
							printf("old value = ");
							for(i = 0; i < 16; i++)
								printf("%x", readBuf[i]);
							printf("\r\n");
						}
						
						if(PcdWrite(0x09, writeBuf) == MI_OK)	//写入新值
						{
							printf("write ok\r\n");
							if(PcdRead(0x09, readBuf) == MI_OK)	//读出写入的值
							{
								printf("new value = ");
								for(i = 0; i < 16; i++)
									printf("%x", readBuf[i]);
								printf("\r\n");
							}
						}
					}
					
					printf("-----------------------------------------\r\n");
					//加减值
					if(PcdAuthState(0x60,0x02,KEY,UID) == MI_OK)	//验证
					{
						printf("auth pass\r\n");
						if(PcdWrite(0x02, data1) == MI_OK)	//要把某块变成钱包才能接收充值和扣款命令
						{
							printf("write ok\r\n");
							if(PcdValue(0xC1, 0x02, addValue) == MI_OK)	//充值
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
							
							if(PcdValue(0xC0, 0x02, subValue) == MI_OK)	//扣款
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




