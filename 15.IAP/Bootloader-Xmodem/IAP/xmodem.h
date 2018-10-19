#ifndef _XMODEM_H
#define _XMODEM_H
#include "sys.h"

#define SOH  0x01
#define STX  0x02
#define EOT  0x04
#define ACK  0x06
#define NAK  0x15
#define CAN  0x18
#define CTRLZ 0x1A


#define CHECK_SUM		0x01
#define CHECK_CRC		0x02

#define CHECK_LEN		CHECK_SUM	//检验占用的字节数

//数据包
typedef struct
{
	u8	m_SOH;
	u8	m_PN;
	u8	m_PN_R;
	u8	m_Data[128];
	u8	check[CHECK_LEN];
}DATA_PACKAGE;	

#endif





