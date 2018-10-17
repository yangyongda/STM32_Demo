#ifndef _SST25VF016B_H
#define _SST25VF016B_H
#include"stm32_spi.h"
#define SPI_FLASH_L GPIO_ResetBits(GPIOE,GPIO_Pin_6);
#define SPI_FLASH_H GPIO_SetBits(GPIOE,GPIO_Pin_6);


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

#endif
