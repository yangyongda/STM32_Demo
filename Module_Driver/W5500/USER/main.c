#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "w5500.h" 
#include <string.h>
 
/************************************************
W5500ʵ��

SPI�ӿ�

ͨ������INT_PROCESS����������ʹ���жϻ���ʹ����ѯ
�ó���ֻʹ����UDP
************************************************/

/*******************************************************************************
* ������  : Process_Socket_Data
* ����    : W5500���ղ����ͽ��յ�������
* ����    : s:�˿ں�
* ���    : ��
* ����ֵ  : ��
* ˵��    : �������ȵ���S_rx_process()��W5500�Ķ˿ڽ������ݻ�������ȡ����,
*			Ȼ�󽫶�ȡ�����ݴ�Rx_Buffer������Temp_Buffer���������д���
*			������ϣ������ݴ�Temp_Buffer������Tx_Buffer������������S_tx_process()
*			�������ݡ�
*******************************************************************************/
void Process_Socket_Data(SOCKET s)
{
	unsigned short size;
	size=Read_SOCK_Data_Buffer(s, Rx_Buffer);
	UDP_DIPR[0] = Rx_Buffer[0];
	UDP_DIPR[1] = Rx_Buffer[1];
	UDP_DIPR[2] = Rx_Buffer[2];
	UDP_DIPR[3] = Rx_Buffer[3];

	UDP_DPORT[0] = Rx_Buffer[4];
	UDP_DPORT[1] = Rx_Buffer[5];
	memcpy(Tx_Buffer, Rx_Buffer+8, size-8);			
	Write_SOCK_Data_Buffer(s, Tx_Buffer, size-8);
}

 int main(void)
 {	
	delay_init();	    //��ʱ������ʼ�
	uart_init(115200);	  
	Set_Net_Parameters();			//�����������
	W5500_Init();							//W5500��ʼ��
	Detect_Gateway();	//������ط����� 
	Socket_Init(0);		//ָ��Socket(0~7)��ʼ��,��ʼ���˿�0
	W5500_Socket_Set();				//UDP 
	 
	while(1)
	{
#ifdef INT_PROCESS
		if(W5500_Interrupt)//����W5500�ж�		
		{
			W5500_Interrupt_Process();//W5500�жϴ��������
		}
#else
		W5500_Interrupt_Process();//W5500�жϴ��������
#endif

		if((S0_Data & S_RECEIVE) == S_RECEIVE)//���Socket0���յ�����
		{
			S0_Data&=~S_RECEIVE;
			Process_Socket_Data(0);//W5500���ղ����ͽ��յ�������
		}
	}
 }


