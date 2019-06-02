#include "Uart.h"


void Uart1_Init(void)
{

	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;	//Ϊ�����ж�ʹ��
	
	//����ʱ�Ӻ�GPIOAʱ��ʹ��  PA10��PA9����ΪRX��TX��ʹ�ø��ù���ʱҪ������Ӧ����ʱ�ӣ�
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA,ENABLE);
	
	//PA9����ΪTX����������Ϊ���
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;//�����������ģʽ
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	//PA10����ΪRX����������Ϊ���룬����ʱ����Ҫ���ô�������
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������ģʽ
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	//Usart1 NVIC ����
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 				//����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���

	//USART1����
	USART_InitStructure.USART_BaudRate =115200;	//���ò�����
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;	//���ݳ���Ϊ8λ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;  //����1λֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No; //��żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//Ӳ�������ƣ�û��
	USART_InitStructure.USART_Mode = USART_Mode_Rx|USART_Mode_Tx;//����Ϊȫ˫��������RX��TXģʽ��Ҫ��
	USART_Init(USART1,&USART_InitStructure);   //USART1��ʼ��
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//�������ڽ����ж�
	USART_Cmd(USART1,ENABLE); 	 //ʹ�ܴ�������
}

void Uart2_Init(void)
{

	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;	//Ϊ�����ж�ʹ��
	
	//����ʱ�Ӻ�GPIOAʱ��ʹ��  PA3��PA2����ΪRX��TX��ʹ�ø��ù���ʱҪ������Ӧ����ʱ�ӣ�
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
	
	//PA2����ΪTX����������Ϊ���
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;//�����������ģʽ
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	//PA3����ΪRX����������Ϊ���룬����ʱ����Ҫ���ô�������
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������ģʽ
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	//Usart2 NVIC ����
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 				//����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
  NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2 ;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���

	//USART2����
	USART_InitStructure.USART_BaudRate =115200;	//���ò�����
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;	//���ݳ���Ϊ8λ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;  //����1λֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No; //��żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//Ӳ�������ƣ�û��
	USART_InitStructure.USART_Mode = USART_Mode_Rx|USART_Mode_Tx;//����Ϊȫ˫��������RX��TXģʽ��Ҫ��
	USART_Init(USART2,&USART_InitStructure);   //USART2��ʼ��
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//�������ڽ����ж�
	USART_Cmd(USART2,ENABLE); 	 //ʹ�ܴ�������
}

u16 Uart2_Send_Buffer(u8 * bytes, u16 num)
{
	u16 i;
	
	for(i = 0; i < num; i++)
	{
		while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET) {}	
		USART_SendData(USART2, (uint8_t) bytes[i]);
	}
	return i;
}
	
void USART2_IRQHandler(void)                	//����2�жϷ������
{
	
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET) //�����ж�
	{
		USART_SendData(USART1, USART_ReceiveData(USART2));
	}
}

void USART1_IRQHandler(void)                	//����1�жϷ������
{
	
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET) //�����ж�
	{
		USART_SendData(USART1, USART_ReceiveData(USART1)); //�ѽ��յ��ķ��ػ�ȥ
	}
}

//ʹ��microLib�ķ���
int fputc(int ch, FILE *f)
{
	while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET) {}	
  USART_SendData(USART1, (uint8_t) ch);
  return ch;
}



