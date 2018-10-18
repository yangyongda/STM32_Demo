#ifndef _SST25VF016B_H
#define _SST25VF016B_H
#include"spi.h"
/*
16Mbit Spi Serial Flash

2M����
*/

/*
�����

0x03  25M�ٶȶ�ȡ
0x0B  50M�ٶȶ�ȡ
0x20  ����4K����
0x52  ����32K��
0xD8  ����64K��
0x60��0xC7 ��������оƬ  
0x02  д��һ���ֽ�
0xAD	�Զ���ַ����
0x05  ��״̬�Ĵ���
0x50  ʹ��д״̬�Ĵ���
0x01  д״̬�Ĵ���
0x06  дʹ��
0x04  д��ֹ
0x90 0xAB ��ȡID
0x9F  ��ȡJEDEC ID
0x70	ʹ��AAI���æ״̬
0x80	��ֹAAI���æ״̬

*/
#define	SST25VFXX_CS 		PEout(6)  //sst25vf016bƬѡ�ź�


u8 Read_Status(void);
void WriteStatus_Enable(void);
void WriteEnable(void);
void WriteDisable(void);
void Check_Busy(void);
u16 Read_DeviceID(void);
void Section_Dell(u32 addr);
void Section_Read(u32 addr,u8 *buffer,u16 Size);
void Section_Write(u32 addr,u8 *buffer,u16 Size);
void Section_All_dell(void);
void SST25VF16B_Init(void);

#endif
