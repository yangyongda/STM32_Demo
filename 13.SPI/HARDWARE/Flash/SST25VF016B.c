#include "SST25VF016B.h"
#include"delay.h"


//初始化SPI FLASH的IO口
void SST25VF16B_Init(void)
{	
  GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOE, ENABLE );//PORTE时钟使能 

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;  // PE6 推挽 
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOE, &GPIO_InitStructure);
 	GPIO_SetBits(GPIOE,GPIO_Pin_6);
 
  SST25VFXX_CS=1;				//SPI FLASH不选中
	SPI1_Init();		   	//初始化SPI
	SPI1_SetSpeed(SPI_BaudRatePrescaler_2);//设置为18M时钟,高速模式

} 

//读取状态寄存器(05h)
u8 Read_Status(void)
{
	u8 dt;
	SST25VFXX_CS = 0;  //自定义宏 ,开始SPI通信
	dt = SPI1_ReadWriteByte(0x05);	//发送指令,并返回数据
	SST25VFXX_CS = 1;
	return dt;
}

//使能写状态寄存器 EWSR、写状态寄存器WRSR

void WriteStatus_Enable(void)
{
	SST25VFXX_CS = 0;
	SPI1_ReadWriteByte(0x50);
	SST25VFXX_CS = 1;
	SST25VFXX_CS = 0;
	SPI1_ReadWriteByte(0x01);
	SPI1_ReadWriteByte(0);	
	SST25VFXX_CS = 1;
	Check_Busy();
}

//写使能
void WriteEnable(void)
{
	SST25VFXX_CS = 0;
	SPI1_ReadWriteByte(0x06);
	SST25VFXX_CS = 1;	
}

//写禁止
void WriteDisable(void)
{
  SST25VFXX_CS = 0;
	SPI1_ReadWriteByte(0x04);
	SST25VFXX_CS = 1;
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

	SST25VFXX_CS = 0;
	SPI1_ReadWriteByte(0x90);
	SPI1_ReadWriteByte(0);
	SPI1_ReadWriteByte(0);
	SPI1_ReadWriteByte(0);

	id=SPI1_ReadWriteByte(0);
	id=id<<8;
	id=id+SPI1_ReadWriteByte(0);
	SST25VFXX_CS = 1;

	return id;
}

//扇区擦除
void Section_Dell(u32 addr)
{
	WriteStatus_Enable();//使能写状态寄存器
	WriteEnable();//写使能

	SST25VFXX_CS = 0;
	SPI1_ReadWriteByte(0x20);
	SPI1_ReadWriteByte((addr&0xFF0000)>>16);//发送地址
	SPI1_ReadWriteByte((addr&0xFF00)>>8);
	SPI1_ReadWriteByte(addr&0xFF);
	SST25VFXX_CS = 1;
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

	SST25VFXX_CS = 0;
	SPI1_ReadWriteByte(0x0B);
	//发送读取的地址
	SPI1_ReadWriteByte((addr&0xFF0000)>>16);
	SPI1_ReadWriteByte((addr&0xFF00)>>8);
	SPI1_ReadWriteByte(addr&0xFF);
	SPI1_ReadWriteByte(0); //发送的值任意

	while(i<Size)
	{
		//读取数据
		buffer[i]=SPI1_ReadWriteByte(0);
		i++;
	}
	SST25VFXX_CS = 1;
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

	SST25VFXX_CS = 0;
	SPI1_ReadWriteByte(0xAD);
	SPI1_ReadWriteByte((addr&0xFF0000)>>16); //发送24位地址
	SPI1_ReadWriteByte((addr&0xFF00)>>8);
	SPI1_ReadWriteByte(addr&0xFF);
	SPI1_ReadWriteByte(buffer[0]);
	SPI1_ReadWriteByte(buffer[1]);
	SST25VFXX_CS = 1;

	i=2;
	while(i<Size)
	{
		delay_us(10);
		SST25VFXX_CS = 0;
		SPI1_ReadWriteByte(0xAD);
		SPI1_ReadWriteByte(buffer[i++]);
		SPI1_ReadWriteByte(buffer[i++]);
		SST25VFXX_CS = 1;
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

	SST25VFXX_CS = 0;
	SPI1_ReadWriteByte(0x60);
	SST25VFXX_CS = 1;
	Check_Busy();
}






