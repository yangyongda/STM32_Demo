#include "xmodem.h"


DATA_PACKAGE dataPkt;
u8 g_CheckType='C';
u8 g_Time_out_Count; 
/**************************************************************************************************
** ������: xmodemReceive
** ��������: xmodemЭ�����
** �������: <checkType> У�鷽ʽ  2: CRCУ�� 1:�ۼӺ�У��
** �������: ��
** ����ֵ: ״̬��
** ����˵��:��
***************************************************************************************************/
u8 xmodemReceive(u8 checkType)
{

	if(checkType==CHECK_CRC){//CRC
		g_CheckType='C';
	}else if(checkType==CHECK_SUM){
		g_CheckType=NAK;
	}
	
	USART_SendData(USART1, g_CheckType);
	
	TIM3_Start(9999);	//1s����һ���ж�
	while(g_Time_out_Count < TIME_OUT && RecSuccess != 1);	// ��û�г�ʱ���߻�û�н������
	TIM3_Stop();
	
	while(dataPkt.m_SOH == SOH)
	{
		if(g_Time_out_Count == TIME_OUT)	//��ʱ
		{
			USART_RX_CNT = 0;
			memset((u8*)&dataPkt, 0, PKT_LEN);
			USART_SendData(USART1, NAK);
		}
		else
		{
			
			if(checkSum((u8*)&dataPkt))
			{
				iap_write_appbin((FLASH_APP1_ADDR + (PackageNo-1) * DATA_LEN),((u8*)&(dataPkt.m_Data)),DATA_LEN);//����FLASH����
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
		
		TIM3_Start(9999);	//1s����һ���ж�
		while(g_Time_out_Count < 10 && RecSuccess != 1);	// ��û�г�ʱ���߻�û�н������
		TIM3_Stop();
	}
	
	return 0;
}

/**************************************************************************************************
** ������: checkSum
** ��������: ����У���
** �������: buf: ���ݰ��׵�ַ
** �������: ��
** ����ֵ: 0��У��ͨ���� 1:У��ʧ��
** ����˵��:��
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
