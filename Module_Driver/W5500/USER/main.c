#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "w5500.h" 
#include <string.h>
 
/************************************************
W5500实验

SPI接口

通过定义INT_PROCESS宏来更改是使用中断还是使用轮询
该程序只使用了UDP
************************************************/

/*******************************************************************************
* 函数名  : Process_Socket_Data
* 描述    : W5500接收并发送接收到的数据
* 输入    : s:端口号
* 输出    : 无
* 返回值  : 无
* 说明    : 本过程先调用S_rx_process()从W5500的端口接收数据缓冲区读取数据,
*			然后将读取的数据从Rx_Buffer拷贝到Temp_Buffer缓冲区进行处理。
*			处理完毕，将数据从Temp_Buffer拷贝到Tx_Buffer缓冲区。调用S_tx_process()
*			发送数据。
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
	delay_init();	    //延时函数初始�
	uart_init(115200);	  
	Set_Net_Parameters();			//设置网络参数
	W5500_Init();							//W5500初始化
	Detect_Gateway();	//检查网关服务器 
	Socket_Init(0);		//指定Socket(0~7)初始化,初始化端口0
	W5500_Socket_Set();				//UDP 
	 
	while(1)
	{
#ifdef INT_PROCESS
		if(W5500_Interrupt)//处理W5500中断		
		{
			W5500_Interrupt_Process();//W5500中断处理程序框架
		}
#else
		W5500_Interrupt_Process();//W5500中断处理程序框架
#endif

		if((S0_Data & S_RECEIVE) == S_RECEIVE)//如果Socket0接收到数据
		{
			S0_Data&=~S_RECEIVE;
			Process_Socket_Data(0);//W5500接收并发送接收到的数据
		}
	}
 }


