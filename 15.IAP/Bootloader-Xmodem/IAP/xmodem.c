#include "xmodem.h"


u8 g_CheckType='C';

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
	
}