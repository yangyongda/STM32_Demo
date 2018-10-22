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

	if(checkType==CHECK_CRC){//CRC
		g_CheckType='C';
	}else if(checkType==CHECK_SUM){
		g_CheckType=NAK;
	}
	
	USART_SendData(USART1, g_CheckType);
	
	TIM3_Start(9999);	//1s产生一次中断
	while(g_Time_out_Count < TIME_OUT && RecSuccess != 1);	// 还没有超时或者还没有接收完成
	TIM3_Stop();
	
	while(dataPkt.m_SOH == SOH)
	{
		if(g_Time_out_Count == TIME_OUT)	//超时
		{
			USART_RX_CNT = 0;
			memset((u8*)&dataPkt, 0, PKT_LEN);
			USART_SendData(USART1, NAK);
		}
		else
		{
			
			if(checkSum((u8*)&dataPkt))
			{
				iap_write_appbin((FLASH_APP1_ADDR + (PackageNo-1) * DATA_LEN),((u8*)&(dataPkt.m_Data)),DATA_LEN);//更新FLASH代码
				USART_SendData(USART1, ACK);
			}
			else
			{
				USART_SendData(USART1, NAK);
			}
			
			USART_RX_CNT = 0;
			PackageNo ++;
			memset((u8*)&dataPkt, 0, PKT_LEN);
		}
		RecSuccess = 0;
		g_Time_out_Count = 0;
		
		TIM3_Start(9999);	//1s产生一次中断
		while(g_Time_out_Count < 10 && RecSuccess != 1);	// 还没有超时或者还没有接收完成
		TIM3_Stop();
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
