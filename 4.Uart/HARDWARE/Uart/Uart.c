#include "Uart.h"


void Uart_Init(void)
{

	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;	//为接收中断使用
	
	//串口时钟和GPIOA时钟使能  PA10和PA9复用为RX和TX（使用复用功能时要开启相应功能时钟）
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA,ENABLE);
	
	//PA9复用为TX，所以配置为输出
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;//复用推挽输出模式
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	//PA10复用为RX，所以配置为输入，输入时不需要配置传输速率
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入模式
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	//Usart1 NVIC 配置
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 				//设置NVIC中断分组2:2位抢占优先级，2位响应优先级
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器

	//USART1配置
	USART_InitStructure.USART_BaudRate =115200;	//设置波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;	//数据长度为8位
	USART_InitStructure.USART_StopBits = USART_StopBits_1;  //配置1位停止位
	USART_InitStructure.USART_Parity = USART_Parity_No; //奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//硬件流控制：没有
	USART_InitStructure.USART_Mode = USART_Mode_Rx|USART_Mode_Tx;//配置为全双工，所以RX和TX模式都要打开
	USART_Init(USART1,&USART_InitStructure);   //USART1初始化
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//开启串口接受中断
	USART_Cmd(USART1,ENABLE); 	 //使能串口外设
}

void USART1_IRQHandler(void)                	//串口1中断服务程序
{
	
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET) //接收中断
	{
		USART_SendData(USART1, USART_ReceiveData(USART1)); //把接收到的返回回去
	}
}

//使用microLib的方法
int fputc(int ch, FILE *f)
{
	while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET) {}	
  USART_SendData(USART1, (uint8_t) ch);
  return ch;
}



