#include "xmodem.h"


u8 g_CheckType='C';

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
	
}