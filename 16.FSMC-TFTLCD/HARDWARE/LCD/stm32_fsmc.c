#include"stm32_fsmc.h"

//FSMC管脚及时钟配置
void GPIO_Configuration(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
	//打开管脚时钟和FSMC时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOD|RCC_APB2Periph_GPIOE,ENABLE);	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_FSMC,ENABLE);

	//FSMC  管脚初始化
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Init(GPIOD,&GPIO_InitStructure);
	GPIO_SetBits(GPIOD,GPIO_Pin_13);//打开背光

	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_1;//复位
	GPIO_Init(GPIOE,&GPIO_InitStructure);
	
	//启用fsmc复用功能 复用上拉模式
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

//FSMC配置
void FSMC_Configuration(void)
{
  FSMC_NORSRAMInitTypeDef  FSMC_NORSRAMInitStructure;
  FSMC_NORSRAMTimingInitTypeDef  p;  

  p.FSMC_AddressSetupTime = 0x02;//地址建立时间
  p.FSMC_AddressHoldTime = 0x00;//地址保持时间
  p.FSMC_DataSetupTime = 0x05;//数据建立时间
  p.FSMC_BusTurnAroundDuration = 0x00;//总线恢复时间
  p.FSMC_CLKDivision = 0x00;//时钟分频
  p.FSMC_DataLatency = 0x00;//数据保持时间
  p.FSMC_AccessMode = FSMC_AccessMode_B;

  //NOR FLASH 的 BANK1
  FSMC_NORSRAMInitStructure.FSMC_Bank = FSMC_Bank1_NORSRAM1;
  //数据线与地址线不复用
  FSMC_NORSRAMInitStructure.FSMC_DataAddressMux = FSMC_DataAddressMux_Disable;
  //存储器类型 NOR FLASH
  FSMC_NORSRAMInitStructure.FSMC_MemoryType = FSMC_MemoryType_NOR;
  //数据宽度为 16 位
  FSMC_NORSRAMInitStructure.FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_16b;
  //使用异步写模式，禁止突发模式
  FSMC_NORSRAMInitStructure.FSMC_BurstAccessMode = FSMC_BurstAccessMode_Disable;
  //本成员的配置只在突发模式下有效，等待信号极性为低
  FSMC_NORSRAMInitStructure.FSMC_WaitSignalPolarity = FSMC_WaitSignalPolarity_Low;
  //禁止非对齐突发模式
  FSMC_NORSRAMInitStructure.FSMC_WrapMode = FSMC_WrapMode_Disable;
  //本成员配置仅在突发模式下有效。NWAIT 信号在什么时期产生
  FSMC_NORSRAMInitStructure.FSMC_WaitSignalActive = FSMC_WaitSignalActive_BeforeWaitState;
  //本成员的配置只在突发模式下有效，禁用 NWAIT 信号
  FSMC_NORSRAMInitStructure.FSMC_WriteOperation = FSMC_WriteOperation_Enable;
  //禁止突发写操作
  FSMC_NORSRAMInitStructure.FSMC_WaitSignal = FSMC_WaitSignal_Disable;
  //写使能
  FSMC_NORSRAMInitStructure.FSMC_ExtendedMode = FSMC_ExtendedMode_Disable;
  //禁止扩展模式，扩展模式可以使用独立的读、写模式
  FSMC_NORSRAMInitStructure.FSMC_WriteBurst = FSMC_WriteBurst_Disable;
  //配置读写时序
  FSMC_NORSRAMInitStructure.FSMC_ReadWriteTimingStruct = &p;
  //配置写时序
  FSMC_NORSRAMInitStructure.FSMC_WriteTimingStruct = &p;

  //初始化FSMC
  FSMC_NORSRAMInit(&FSMC_NORSRAMInitStructure); 
  //使能FSMC BANK1_SRAM 模式
  FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM1, ENABLE);  
}

void FSMC_Init(void)
{
	GPIO_Configuration();
	FSMC_Configuration();	
}



