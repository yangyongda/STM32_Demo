#ifndef _SST25VF016B_H
#define _SST25VF016B_H
#include"spi.h"
/*
16Mbit Spi Serial Flash

2M容量
*/

/*
命令表

0x03  25M速度读取
0x0B  50M速度读取
0x20  擦除4K扇区
0x52  擦除32K块
0xD8  擦除64K块
0x60或0xC7 擦除整个芯片  
0x02  写入一个字节
0xAD	自动地址增加
0x05  读状态寄存器
0x50  使能写状态寄存器
0x01  写状态寄存器
0x06  写使能
0x04  写禁止
0x90 0xAB 读取ID
0x9F  读取JEDEC ID
0x70	使能AAI输出忙状态
0x80	禁止AAI输出忙状态

*/
#define	SST25VFXX_CS 		PEout(6)  //sst25vf016b片选信号


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
