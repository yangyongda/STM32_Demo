#include"stm32_fsmc.h"

//FSMC�ܽż�ʱ������
void GPIO_Configuration(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
	//�򿪹ܽ�ʱ�Ӻ�FSMCʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOD|RCC_APB2Periph_GPIOE,ENABLE);	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_FSMC,ENABLE);

	//FSMC  �ܽų�ʼ��
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Init(GPIOD,&GPIO_InitStructure);
	GPIO_SetBits(GPIOD,GPIO_Pin_13);//�򿪱���

	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_1;//��λ
	GPIO_Init(GPIOE,&GPIO_InitStructure);
	
	//����fsmc���ù��� ��������ģʽ
	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_14 //D0
								|GPIO_Pin_15 //D1
								|GPIO_Pin_0	 //D2
								|GPIO_Pin_1	 //D3
								|GPIO_Pin_8	 //D13
								|GPIO_Pin_9	 //D14
								|GPIO_Pin_10;//D15
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_Init(GPIOD,&GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_7	 //D4
								|GPIO_Pin_8	 //D5
								|GPIO_Pin_9	 //D6
								|GPIO_Pin_10 //D7
								|GPIO_Pin_11 //D8
								|GPIO_Pin_12 //D9
								|GPIO_Pin_13 //D10
								|GPIO_Pin_14 //D11
								|GPIO_Pin_15;//D12
	GPIO_Init(GPIOE,&GPIO_InitStructure);


	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_11 //RS
								|GPIO_Pin_4	 //nOE
								|GPIO_Pin_5; //nWE
	GPIO_Init(GPIOD,&GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_7; //NE1
	GPIO_Init(GPIOD,&GPIO_InitStructure);
}

//FSMC����
void FSMC_Configuration(void)
{
  FSMC_NORSRAMInitTypeDef  FSMC_NORSRAMInitStructure;
  FSMC_NORSRAMTimingInitTypeDef  p;  

  p.FSMC_AddressSetupTime = 0x02;//��ַ����ʱ��
  p.FSMC_AddressHoldTime = 0x00;//��ַ����ʱ��
  p.FSMC_DataSetupTime = 0x05;//���ݽ���ʱ��
  p.FSMC_BusTurnAroundDuration = 0x00;//���߻ָ�ʱ��
  p.FSMC_CLKDivision = 0x00;//ʱ�ӷ�Ƶ
  p.FSMC_DataLatency = 0x00;//���ݱ���ʱ��
  p.FSMC_AccessMode = FSMC_AccessMode_B;

  //NOR FLASH �� BANK1
  FSMC_NORSRAMInitStructure.FSMC_Bank = FSMC_Bank1_NORSRAM1;
  //���������ַ�߲�����
  FSMC_NORSRAMInitStructure.FSMC_DataAddressMux = FSMC_DataAddressMux_Disable;
  //�洢������ NOR FLASH
  FSMC_NORSRAMInitStructure.FSMC_MemoryType = FSMC_MemoryType_NOR;
  //���ݿ��Ϊ 16 λ
  FSMC_NORSRAMInitStructure.FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_16b;
  //ʹ���첽дģʽ����ֹͻ��ģʽ
  FSMC_NORSRAMInitStructure.FSMC_BurstAccessMode = FSMC_BurstAccessMode_Disable;
  //����Ա������ֻ��ͻ��ģʽ����Ч���ȴ��źż���Ϊ��
  FSMC_NORSRAMInitStructure.FSMC_WaitSignalPolarity = FSMC_WaitSignalPolarity_Low;
  //��ֹ�Ƕ���ͻ��ģʽ
  FSMC_NORSRAMInitStructure.FSMC_WrapMode = FSMC_WrapMode_Disable;
  //����Ա���ý���ͻ��ģʽ����Ч��NWAIT �ź���ʲôʱ�ڲ���
  FSMC_NORSRAMInitStructure.FSMC_WaitSignalActive = FSMC_WaitSignalActive_BeforeWaitState;
  //����Ա������ֻ��ͻ��ģʽ����Ч������ NWAIT �ź�
  FSMC_NORSRAMInitStructure.FSMC_WriteOperation = FSMC_WriteOperation_Enable;
  //��ֹͻ��д����
  FSMC_NORSRAMInitStructure.FSMC_WaitSignal = FSMC_WaitSignal_Disable;
  //дʹ��
  FSMC_NORSRAMInitStructure.FSMC_ExtendedMode = FSMC_ExtendedMode_Disable;
  //��ֹ��չģʽ����չģʽ����ʹ�ö����Ķ���дģʽ
  FSMC_NORSRAMInitStructure.FSMC_WriteBurst = FSMC_WriteBurst_Disable;
  //���ö�дʱ��
  FSMC_NORSRAMInitStructure.FSMC_ReadWriteTimingStruct = &p;
  //����дʱ��
  FSMC_NORSRAMInitStructure.FSMC_WriteTimingStruct = &p;

  //��ʼ��FSMC
  FSMC_NORSRAMInit(&FSMC_NORSRAMInitStructure); 
  //ʹ��FSMC BANK1_SRAM ģʽ
  FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM1, ENABLE);  
}

void FSMC_Init(void)
{
	GPIO_Configuration();
	FSMC_Configuration();	
}



