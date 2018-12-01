#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "w5500.h" 
#include <string.h>
 
/************************************************
W5500ÊµÑé

SPI½Ó¿Ú

Í¨¹ı¶¨ÒåINT_PROCESSºêÀ´¸ü¸ÄÊÇÊ¹ÓÃÖĞ¶Ï»¹ÊÇÊ¹ÓÃÂÖÑ¯
¸Ã³ÌĞòÖ»Ê¹ÓÃÁËUDP
************************************************/

/*******************************************************************************
* º¯ÊıÃû  : Process_Socket_Data
* ÃèÊö    : W5500½ÓÊÕ²¢·¢ËÍ½ÓÊÕµ½µÄÊı¾İ
* ÊäÈë    : s:¶Ë¿ÚºÅ
* Êä³ö    : ÎŞ
* ·µ»ØÖµ  : ÎŞ
* ËµÃ÷    : ±¾¹ı³ÌÏÈµ÷ÓÃS_rx_process()´ÓW5500µÄ¶Ë¿Ú½ÓÊÕÊı¾İ»º³åÇø¶ÁÈ¡Êı¾İ,
*			È»ºó½«¶ÁÈ¡µÄÊı¾İ´ÓRx_Buffer¿½±´µ½Temp_Buffer»º³åÇø½øĞĞ´¦Àí¡£
*			´¦ÀíÍê±Ï£¬½«Êı¾İ´ÓTemp_Buffer¿½±´µ½Tx_Buffer»º³åÇø¡£µ÷ÓÃS_tx_process()
*			·¢ËÍÊı¾İ¡£
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
	delay_init();	    //ÑÓÊ±º¯Êı³õÊ¼»
	uart_init(115200);	  
	Set_Net_Parameters();			//ÉèÖÃÍøÂç²ÎÊı
	W5500_Init();							//W5500³õÊ¼»¯
	Detect_Gateway();	//¼ì²éÍø¹Ø·şÎñÆ÷ 
	Socket_Init(0);		//Ö¸¶¨Socket(0~7)³õÊ¼»¯,³õÊ¼»¯¶Ë¿Ú0
	W5500_Socket_Set();				//UDP 
	 
	while(1)
	{
#ifdef INT_PROCESS
		if(W5500_Interrupt)//´¦ÀíW5500ÖĞ¶Ï		
		{
			W5500_Interrupt_Process();//W5500ÖĞ¶Ï´¦Àí³ÌĞò¿ò¼Ü
		}
#else
		W5500_Interrupt_Process();//W5500ÖĞ¶Ï´¦Àí³ÌĞò¿ò¼Ü
#endif

		if((S0_Data & S_RECEIVE) == S_RECEIVE)//Èç¹ûSocket0½ÓÊÕµ½Êı¾İ
		{
			S0_Data&=~S_RECEIVE;
			Process_Socket_Data(0);//W5500½ÓÊÕ²¢·¢ËÍ½ÓÊÕµ½µÄÊı¾İ
		}
	}
 }


