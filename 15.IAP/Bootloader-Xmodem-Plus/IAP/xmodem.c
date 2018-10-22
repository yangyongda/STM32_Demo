#include "xmodem.h"


DATA_PACKAGE dataPkt;
u8 g_CheckType='C';
u8 g_Time_out_Count;
/**************************************************************************************************
** 函数名: xmodemReceive
** 功能描述: xmodem协议接收
** 输入参数: <checkType> 校验方式  2: CRC校验 1:累加和校验
** 输出参数: 无
** 返回值: 状态码
** 其他说明:无
***************************************************************************************************/
u8 xmodemReceive(u8 checkType)
{

	u8 ch = 0;
	u8 i;
	
	if(checkType==CHECK_CRC){//CRC
		g_CheckType='C';
	}else if(checkType==CHECK_SUM){
		g_CheckType=NAK;
	}


	while(1)
	{
		TIM3_Start(9999);
		while(ch == 0)
		{
			USART_SendData(USART1, g_CheckType);
			delay_ms(1000);
			if(g_Time_out_Count > TIME_OUT)
				break;
			
			ch = readChar();
		}
		g_Time_out_Count = 0;
		TIM3_Stop();
		
		while(ch == SOH)
		{
			dataPkt.m_SOH = SOH;
			dataPkt.m_PN = readChar();
			dataPkt.m_PN_R = readChar();
			if(dataPkt.m_PN == ~dataPkt.m_PN_R)
			{
				for(i = 0; i < DATA_LEN; i++)
				{
					dataPkt.m_Data[i] = readChar();
				}
				
				dataPkt.check[0] = readChar();
				
				if(dataPkt.check[0] == checkSum(((u8*)&dataPkt)))
				{
					iap_write_appbin(FLASH_APP1_ADDR + (dataPkt.m_PN - 1)*DATA_LEN ,((u8*)&dataPkt),DATA_LEN);//更新FLASH代码  
					USART_SendData(USART1, ACK);
				}
				else
				{
					USART_SendData(USART1, NAK);
				}
				
			}
			else
			{
				USART_SendData(USART1, NAK);
			}
			USART_RX_CNT = 0;
			READ_CNT = 0;
			memset(((u8*)&dataPkt), 0, PKT_LEN);
			
			TIM3_Start(9999);
			do{
				ch = readChar();
				if(g_Time_out_Count > 5)
					break;
			}while(ch == 0);
			g_Time_out_Count = 0;
			TIM3_Stop();
			
		}
		
		if(ch == EOT)
		{
			USART_SendData(USART1, ACK);
			return 0;
		}
		
	}
	
}

/**************************************************************************************************
** 函数名: checkSum
** 功能描述: 计算校验和
** 输入参数: buf: 数据包首地址
** 输出参数: 无
** 返回值: 0：校验通过， 1:校验失败
** 其他说明:无
***************************************************************************************************/
u8 checkSum(u8* buf)
{
	u8 i;
	u8 sum = 0;
	
	for(i = 0; i < PKT_LEN-1; i++)
	{
		sum += buf[i];
	}
	
	if(sum == buf[PKT_LEN -1])
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

u8 readChar(void)
{
	if(READ_CNT <= USART_RX_CNT)
	{
		u8 ch = USART_RX_BUF[READ_CNT++];
		return ch;
	}
	else
	{
		USART_RX_CNT = 0;
		READ_CNT = 0;
		return 0;
	}
}

