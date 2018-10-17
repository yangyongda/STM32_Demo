#include "SST25VF016B.h"
#include"delay.h"
//��ȡ״̬�Ĵ���(05h)
u8 Read_Status(void)
{
	u8 dt;
	SPI_FLASH_L;  //�Զ���� ,��ʼSPIͨ��
	SPI_SendByte(0x05);	//����ָ��
	dt=SPI_SendByte(0);
	SPI_FLASH_H;
	return dt;
}

//ʹ��д״̬�Ĵ��� EWSR��д״̬�Ĵ���WRSR

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

//дʹ��
void WriteEnable(void)
{
	SPI_FLASH_L;
	SPI_SendByte(0x06);
	SPI_FLASH_H;	
}

//д��ֹ
void WriteDisable(void)
{
    SPI_FLASH_L;
	SPI_SendByte(0x04);
	SPI_FLASH_H;
	Check_Busy();
}
//æ���
void Check_Busy(void)
{
	while((Read_Status()&0x01)==1) ;
}
//������ID
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

//��������
void Section_Dell(u32 addr)
{
	WriteStatus_Enable();//ʹ��д״̬�Ĵ���
	WriteEnable();//дʹ��

	SPI_FLASH_L;
	SPI_SendByte(0x20);
	SPI_SendByte((addr&0xFF0000)>>16);//���͵�ַ
	SPI_SendByte((addr&0xFF00)>>8);
	SPI_SendByte(addr&0xFF);
	SPI_FLASH_H;
	Check_Busy();//æ���
}

/*
  addr----Ҫ��ȡ���ݵ��׵�ַ
  buffer----��Ŷ�ȡ������
  Size-----��ȡ���ֽ���
*/
//������
void Section_Read(u32 addr,u8 *buffer,u16 Size)
{
	u16 i=0;

	SPI_FLASH_L;
	SPI_SendByte(0x0B);
	//���Ͷ�ȡ�ĵ�ַ
	SPI_SendByte((addr&0xFF0000)>>16);
	SPI_SendByte((addr&0xFF00)>>8);
	SPI_SendByte(addr&0xFF);
	SPI_SendByte(0); //���͵�ֵ����

	while(i<Size)
	{
		//��ȡ����
		buffer[i]=SPI_SendByte(0);
		i++;
	}
	SPI_FLASH_H;
}

/*
  addr----Ҫд�����ݵ��׵�ַ
  buffer----Ҫд�������
  Size-----д����ֽ���
*/
//д������ADh��
void Section_Write(u32 addr,u8 *buffer,u16 Size)
{
	u16 i=0;

	Section_Dell(addr);//�Ȳ���

	WriteStatus_Enable();//ʹ��д״̬�Ĵ���
	WriteEnable();//дʹ��

	SPI_FLASH_L;
	SPI_SendByte(0xAD);
	SPI_SendByte((addr&0xFF0000)>>16); //����24λ��ַ
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
	WriteDisable();//�˳�AAIģʽ
	Check_Busy();
}

//ȫоƬ����
void Section_All_dell(void)
{
	WriteStatus_Enable();//ʹ��д״̬�Ĵ���
	WriteEnable();//дʹ��

	SPI_FLASH_L;
	SPI_SendByte(0x60);
	SPI_FLASH_H;
	Check_Busy();
}






