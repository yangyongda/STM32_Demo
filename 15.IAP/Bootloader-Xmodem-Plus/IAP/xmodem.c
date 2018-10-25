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
	u16 crc;
	
	if(checkType==CHECK_CRC){//CRC
		g_CheckType='C';
	}else if(checkType==CHECK_SUM){
		g_CheckType=NAK;
	}



		TIM3_Start(9999);
		do{
			USART_SendData(USART1, g_CheckType);
			delay_ms(1000);
			delay_ms(1000);
			delay_ms(1000);
			if(g_Time_out_Count > TIME_OUT)
				break;
			
			ch = readChar();
		}while(ch == 0);
		g_Time_out_Count = 0;
		TIM3_Stop();
		
		while(ch == SOH)
		{
			dataPkt.m_SOH = SOH;
			//dataPkt.m_PN = readChar();
			//dataPkt.m_PN_R = readChar();
			readBuffer(&(dataPkt.m_PN), 1);
			readBuffer(&(dataPkt.m_PN_R), 1);
			
			if(dataPkt.m_PN == (u8)(~dataPkt.m_PN_R))
			{
				/*
				for(i = 0; i < DATA_LEN; i++)
				{
					dataPkt.m_Data[i] = readChar();
				}
				
				dataPkt.check[0] = readChar();
				dataPkt.check[1] = readChar();
				*/
				readBuffer(dataPkt.m_Data, 130);
				
				crc = ((dataPkt.check[0]<<8)|dataPkt.check[1]);
				
				if( crc == checkCrc(((u8*)&(dataPkt.m_Data)), PKT_LEN - 5))
				{
					iap_write_appbin(FLASH_APP1_ADDR + (dataPkt.m_PN - 1)*DATA_LEN ,((u8*)&(dataPkt.m_Data)),DATA_LEN);//更新FLASH代码  
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
	
		return 0;
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

/**************************************************************************************************
** 函数名: checkCrc
** 功能描述: 计算CRC校验
** 输入参数: buf: 数据包首地址
** 输出参数: 无
** 返回值: 0：校验通过， 1:校验失败
** 其他说明:无
***************************************************************************************************/
u16 checkCrc(u8* buf, u16 size)
{
	u16 wCRCin = 0x0000;
  u16 wCPoly = 0x1021;
  u8  wChar = 0;
  int i;
	
  while (size--) 	
  {
        wChar = *(buf++);
        wCRCin ^= (wChar << 8);
        for( i = 0;i < 8;i++)
        {
          if(wCRCin & 0x8000)
            wCRCin = (wCRCin << 1) ^ wCPoly;
          else
            wCRCin = wCRCin << 1;
        }
  }
  return wCRCin;
}


u8 readChar(void)
{
	if(READ_CNT < USART_RX_CNT)
	{
		u8 ch = USART_RX_BUF[READ_CNT++];
		return ch;
	}
	else
	{
		if(READ_CNT == PKT_LEN)
		{
			USART_RX_CNT = 0;
			READ_CNT = 0;
		}
		return 0;
	}
	
}

u16 readBuffer(u8* buffer, u16 count)
{
	u16 read_cnt = 0;
	TIM3_Start(9999);
	while(read_cnt < count)
	{
		if(READ_CNT < USART_RX_CNT)	//收到数据了
		{
			buffer[read_cnt] = readChar();
			read_cnt++;
		}
		
		if(g_Time_out_Count > 2)
			break;
	}
	g_Time_out_Count = 0;
	TIM3_Stop();
	
	return read_cnt;
}
