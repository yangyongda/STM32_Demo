#include "SST25VF016B.h"
#include"delay.h"


//��ʼ��SPI FLASH��IO��
void SST25VF16B_Init(void)
{	
  GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOE, ENABLE );//PORTEʱ��ʹ�� 

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;  // PE6 ���� 
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOE, &GPIO_InitStructure);
 	GPIO_SetBits(GPIOE,GPIO_Pin_6);
 
  SST25VFXX_CS=1;				//SPI FLASH��ѡ��
	SPI1_Init();		   	//��ʼ��SPI
	SPI1_SetSpeed(SPI_BaudRatePrescaler_2);//����Ϊ18Mʱ��,����ģʽ

} 

//��ȡ״̬�Ĵ���(05h)
u8 Read_Status(void)
{
	u8 dt;
	SST25VFXX_CS = 0;  //�Զ���� ,��ʼSPIͨ��
	dt = SPI1_ReadWriteByte(0x05);	//����ָ��,����������
	SST25VFXX_CS = 1;
	return dt;
}

//ʹ��д״̬�Ĵ��� EWSR��д״̬�Ĵ���WRSR

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

//дʹ��
void WriteEnable(void)
{
	SST25VFXX_CS = 0;
	SPI1_ReadWriteByte(0x06);
	SST25VFXX_CS = 1;	
}

//д��ֹ
void WriteDisable(void)
{
  SST25VFXX_CS = 0;
	SPI1_ReadWriteByte(0x04);
	SST25VFXX_CS = 1;
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

//��������
void Section_Dell(u32 addr)
{
	WriteStatus_Enable();//ʹ��д״̬�Ĵ���
	WriteEnable();//дʹ��

	SST25VFXX_CS = 0;
	SPI1_ReadWriteByte(0x20);
	SPI1_ReadWriteByte((addr&0xFF0000)>>16);//���͵�ַ
	SPI1_ReadWriteByte((addr&0xFF00)>>8);
	SPI1_ReadWriteByte(addr&0xFF);
	SST25VFXX_CS = 1;
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

	SST25VFXX_CS = 0;
	SPI1_ReadWriteByte(0x0B);
	//���Ͷ�ȡ�ĵ�ַ
	SPI1_ReadWriteByte((addr&0xFF0000)>>16);
	SPI1_ReadWriteByte((addr&0xFF00)>>8);
	SPI1_ReadWriteByte(addr&0xFF);
	SPI1_ReadWriteByte(0); //���͵�ֵ����

	while(i<Size)
	{
		//��ȡ����
		buffer[i]=SPI1_ReadWriteByte(0);
		i++;
	}
	SST25VFXX_CS = 1;
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

	SST25VFXX_CS = 0;
	SPI1_ReadWriteByte(0xAD);
	SPI1_ReadWriteByte((addr&0xFF0000)>>16); //����24λ��ַ
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
	WriteDisable();//�˳�AAIģʽ
	Check_Busy();
}

//ȫоƬ����
void Section_All_dell(void)
{
	WriteStatus_Enable();//ʹ��д״̬�Ĵ���
	WriteEnable();//дʹ��

	SST25VFXX_CS = 0;
	SPI1_ReadWriteByte(0x60);
	SST25VFXX_CS = 1;
	Check_Busy();
}






