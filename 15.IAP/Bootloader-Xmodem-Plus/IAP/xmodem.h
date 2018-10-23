#ifndef _XMODEM_H
#define _XMODEM_H
#include "sys.h"
#include "usart.h"
#include "timer.h"
#include "string.h"
#include "iap.h"
#include "delay.h"

#define SOH  0x01
#define STX  0x02
#define EOT  0x04
#define ACK  0x06
#define NAK  0x15
#define CAN  0x18
#define CTRLZ 0x1A


#define CHECK_SUM		0x01
#define CHECK_CRC		0x02

#define CHECK_LEN		CHECK_CRC	//检验占用的字节数
#define PKT_LEN 133	//数据包长度
#define DATA_LEN 128 //数据长度
#define TIME_OUT 60		//超时时间60s

//数据包
typedef struct
{
	u8	m_SOH;
	u8	m_PN;
	u8	m_PN_R;
	u8	m_Data[DATA_LEN];
	u8	check[CHECK_LEN];
}DATA_PACKAGE;	

extern u8 g_Time_out_Count; 
extern DATA_PACKAGE dataPkt;


u8 checkSum(u8* buf);
u16 checkCrc(u8* buf, u16 size);
u8 xmodemReceive(u8 checkType);
u8 readChar(void);

#endif





