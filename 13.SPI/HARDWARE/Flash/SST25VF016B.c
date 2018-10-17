#include "SST25VF016B.h"
#include"delay.h"
//读取状态寄存器(05h)
u8 Read_Status(void)
{
	u8 dt;
	SPI_FLASH_L;  //自定义宏 ,开始SPI通信
	SPI_SendByte(0x05);	//发送指令
	dt=SPI_SendByte(0);
	SPI_FLASH_H;
	return dt;
}

//使能写状态寄存器 EWSR、写状态寄存器WRSR

void WriteStatus_Enable(void)
{
	SPI_FLASH_L;
	SPI_SendByte(0x50);
	SPI_FLASH_H;
	SPI_FLASH_L;
	SPI_SendByte(0x01);
	SPI_SendByte(0);	
	SPI_FLASH_H;
	Check_Busy();
}

//写使能
void WriteEnable(void)
{
	SPI_FLASH_L;
	SPI_SendByte(0x06);
	SPI_FLASH_H;	
}

//写禁止
void WriteDisable(void)
{
    SPI_FLASH_L;
	SPI_SendByte(0x04);
	SPI_FLASH_H;
	Check_Busy();
}
//忙检测
void Check_Busy(void)
{
	while((Read_Status()&0x01)==1) ;
}
//读器件ID
u16 Read_DeviceID(void)
{
	u16 id=0;

	SPI_FLASH_L;
	SPI_SendByte(0x90);
	SPI_SendByte(0);
	SPI_SendByte(0);
	SPI_SendByte(0);

	id=SPI_SendByte(0);
	id=id<<8;
	id=id+SPI_SendByte(0);
	SPI_FLASH_H;

	return id;
}

//扇区擦除
void Section_Dell(u32 addr)
{
	WriteStatus_Enable();//使能写状态寄存器
	WriteEnable();//写使能

	SPI_FLASH_L;
	SPI_SendByte(0x20);
	SPI_SendByte((addr&0xFF0000)>>16);//发送地址
	SPI_SendByte((addr&0xFF00)>>8);
	SPI_SendByte(addr&0xFF);
	SPI_FLASH_H;
	Check_Busy();//忙检测
}

/*
  addr----要读取数据的首地址
  buffer----存放读取的数据
  Size-----读取的字节数
*/
//扇区读
void Section_Read(u32 addr,u8 *buffer,u16 Size)
{
	u16 i=0;

	SPI_FLASH_L;
	SPI_SendByte(0x0B);
	//发送读取的地址
	SPI_SendByte((addr&0xFF0000)>>16);
	SPI_SendByte((addr&0xFF00)>>8);
	SPI_SendByte(addr&0xFF);
	SPI_SendByte(0); //发送的值任意

	while(i<Size)
	{
		//读取数据
		buffer[i]=SPI_SendByte(0);
		i++;
	}
	SPI_FLASH_H;
}

/*
  addr----要写入数据的首地址
  buffer----要写入的数据
  Size-----写入的字节数
*/
//写扇区（ADh）
void Section_Write(u32 addr,u8 *buffer,u16 Size)
{
	u16 i=0;

	Section_Dell(addr);//先擦除

	WriteStatus_Enable();//使能写状态寄存器
	WriteEnable();//写使能

	SPI_FLASH_L;
	SPI_SendByte(0xAD);
	SPI_SendByte((addr&0xFF0000)>>16); //发送24位地址
	SPI_SendByte((addr&0xFF00)>>8);
	SPI_SendByte(addr&0xFF);
	SPI_SendByte(buffer[0]);
	SPI_SendByte(buffer[1]);
	SPI_FLASH_H;

	i=2;
	while(i<Size)
	{
		delay_us(10);
		SPI_FLASH_L;
		SPI_SendByte(0xAD);
		SPI_SendByte(buffer[i++]);
		SPI_SendByte(buffer[i++]);
		SPI_FLASH_H;
	}

	delay_us(10);
	WriteDisable();//退出AAI模式
	Check_Busy();
}

//全芯片擦除
void Section_All_dell(void)
{
	WriteStatus_Enable();//使能写状态寄存器
	WriteEnable();//写使能

	SPI_FLASH_L;
	SPI_SendByte(0x60);
	SPI_FLASH_H;
	Check_Busy();
}






