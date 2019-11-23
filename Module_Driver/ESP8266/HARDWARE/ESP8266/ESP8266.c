#include "ESP8266.h"
#include "uart.h"
#include "delay.h"

/*
	��λģ�� AT+RST
*/
void resetModule(void)
{
	char buffer[20];
	sprintf(buffer, "%s\r\n", (char*)MODULE_RESET);
	Uart2_Send_Buffer((u8*)buffer, 8);
}

/*
	SDK�汾��Ϣ
*/
void getVersion(void)
{
	char buffer[20];
	sprintf(buffer, "%s\r\n", (char*)VERSION_INFO);
	Uart2_Send_Buffer((u8*)buffer, 8);
}

/*
��������:����WIFIģʽ
����˵��: mode: ģʽ, ȡֵ(1:STA, 2:AP 3:AP+STA)
*/
void setWifiMode(u8 mode)
{
	char buffer[20];
	sprintf(buffer, "%s=%d\r\n", (char*)WIFI_MODE, mode);
	Uart2_Send_Buffer((u8*)buffer, 13);
}

/*
��������: ����·����
����˵��: ssid: wifi����
					password: wifi���� 
*/
void setConnectWifi(char* ssid, char* password)
{
	char buffer[60];
	sprintf(buffer, "%s=\"%s\",\"%s\"\r\n", (char*)CONNECT_WIFI, ssid, password);
	Uart2_Send_Buffer((u8*)buffer, 60);
}
/*
��������: ��ȡWifi(AP)�б�
*/
void getWifiList(void)
{
	char buffer[20];
	sprintf(buffer, "%s\r\n", (char*)WIFI_LIST);
	Uart2_Send_Buffer((u8*)buffer, 10);
}

/*
��������: �Ͽ�wifi����
*/
void setDisConnectWifi(void)
{
	char buffer[20];
	sprintf(buffer, "%s\r\n", (char*)DISCONNECT_WIFI);
	Uart2_Send_Buffer((u8*)buffer, 10);
}

/*
��������:��ȡ����״̬
*/
void getConnectStatus(void)
{
	char buffer[20];
	sprintf(buffer, "%s\r\n", (char*)CONNECT_STATUS);
	Uart2_Send_Buffer((u8*)buffer, 14);
}

/*
��������:����TCP(client/server)/UDP
����˵��: type: ���� 1: UDP 2: TCP server 3: TCP client
					remoteIP: Զ��IP
					remotePort: Զ�̶˿�
					localPort: ���ض˿�			
*/
void createTcpOrUdp(u8 type, char* remoteIP, u16 remotePort, u16 localPort)
{
	char buffer[60];
	if(type == 1)
	{
		sprintf(buffer, "%s=\"UDP\",\"%s\",%d,%d,0\r\n", (char*)CREATE_TCP_UDP, remoteIP,remotePort, localPort);
	}
	else if(type == 2)
	{
		sprintf(buffer, "%s=1,%d\r\n", CONFIG_SERVER,localPort);
	}
	else if(type == 3)
	{
		sprintf(buffer, "%s=\"TCP\",\"%s\",%d\r\n", (char*)CREATE_TCP_UDP, remoteIP,remotePort);
	}
	
	Uart2_Send_Buffer((u8*)buffer, 60);
}
/*
��������:����͸��ģʽ
����˵��: mode: 1:͸��ģʽ  0:��͸��ģʽ
*/
void setOSPF(u8 mode)
{
	char buffer[20];
	sprintf(buffer, "%s=%d\r\n", (char*)SET_MODULE_TRAN_MODE, mode);
	Uart2_Send_Buffer((u8*)buffer, 14);
}

/*
��������:��������
����˵��: type: ���� 1: UDP 2: TCP server 3: TCP client
					id: TCP server������ʱʹ�õ�id��, �������TCP Server�ʹ�0
					num:���͵��ֽ���
ע��: ���id =0 num = 0�����͸��(ǰ����AT+CIPMODE=1)
*/
void sendData(u8 type, u8 id, u16 num)
{
	char buffer[20];
	
	
	if(type == UDP)
	{
		sprintf(buffer, "%s\r\n", (char*)SEND_DATA);
	}
	else if(type == TCP_CIENTS)
	{
		sprintf(buffer, "%s=%d\r\n", (char*)SEND_DATA, num);
	}
	else
	{
		sprintf(buffer, "%s=%d,%d\r\n", (char*)SEND_DATA, id, num);
	}
	
	Uart2_Send_Buffer((u8*)buffer, 20);
}

/*
��������:�ر�TCP��UDP
*/
void closeTcpOrUdp(void)
{
	char buffer[20];
	sprintf(buffer, "%s\r\n", (char*)CLOSE_TCP_UDP);
	Uart2_Send_Buffer((u8*)buffer, 20);
}

/*
��������:��ȡIP��ַ
*/
void getIpAddress(void)
{
	char buffer[20];
	sprintf(buffer, "%s\r\n", (char*)GET_IP);
	Uart2_Send_Buffer((u8*)buffer, 20);
}

/*
��������:���ö�����
����˵��:mode: 0:������ 1:������
*/
void setMuxConnect(u8 mode)
{
	char buffer[20];
	sprintf(buffer, "%s=%d\r\n", (char*)START_MUX_CONNECT, mode);
	Uart2_Send_Buffer((u8*)buffer, 20);
}

/*
��������:���÷������Ͽ����ӳ�ʱʱ��
����˵��:timeout:��ʱʱ��
*/
void setConnectTimeOut(u16 timeout)
{
	char buffer[20];
	sprintf(buffer, "%s=%d\r\n", (char*)SET_TIMEOUT, timeout);
	Uart2_Send_Buffer((u8*)buffer, 20);
}
/*
��������: ����AP����
*/
void setAPPara(char* ssid, char* password, u8 channel, u8 encrypt)
{
	char buffer[60];
	sprintf(buffer, "%s=\"%s\",\"%s\",%d,%d\r\n", (char*)SET_AP_PARA, ssid, password, channel, encrypt);
	Uart2_Send_Buffer((u8*)buffer, 60);
}
	
void CH_PD_Init(void)
{
 
	GPIO_InitTypeDef  GPIO_InitStructure;	//GPIO���ýṹ��

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);	 //ʹ��PB,PD�˿�ʱ��

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;				 			
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
	GPIO_Init(GPIOC, &GPIO_InitStructure);					 		//�����趨������ʼ��GPIOC.7
	GPIO_ResetBits(GPIOC,GPIO_Pin_7);						 				//PC.7 �����

}

void initEsp8266(char* ssid, char* password)
{
	Uart2_Init();	//��ʼ������
	CH_PD_Init();
	delay_ms(300);
	CH_PD_PIN = 1;
	delay_ms(1000);
	delay_ms(1000);
	delay_ms(1000);
	delay_ms(1000);
	delay_ms(1000);
}

void STA_UDP_Mode(void)
{
	setWifiMode(STA_MODE);
	delay_ms(1000);
	delay_ms(1000);
	delay_ms(1000);
	delay_ms(1000);
	delay_ms(1000);
	setConnectWifi(SSID, PASSWORD);
	delay_ms(1000);
	delay_ms(1000);
	delay_ms(1000);
	delay_ms(1000);
	delay_ms(1000);
	delay_ms(1000);
	delay_ms(1000);
	delay_ms(1000);
	delay_ms(1000);
	delay_ms(1000);
	createTcpOrUdp(UDP, REMOTEIP, 8080, 9000);
	delay_ms(1000);
	delay_ms(1000);
	delay_ms(1000);
	delay_ms(1000);
	delay_ms(1000);
	setOSPF(1);
	delay_ms(1000);
	delay_ms(1000);
	delay_ms(1000);
	delay_ms(1000);
	delay_ms(1000);
	sendData(UDP, 0, 0);
}

void STA_TCP_Server(void)
{
	setWifiMode(STA_MODE);
	delay_ms(1000);
	delay_ms(1000);
	delay_ms(1000);
	delay_ms(1000);
	delay_ms(1000);
	setConnectWifi(SSID, PASSWORD);
	delay_ms(1000);
	delay_ms(1000);
	delay_ms(1000);
	delay_ms(1000);
	delay_ms(1000);
	delay_ms(1000);
	delay_ms(1000);
	delay_ms(1000);
	delay_ms(1000);
	delay_ms(1000);
	setMuxConnect(1);
	delay_ms(1000);
	delay_ms(1000);
	delay_ms(1000);
	delay_ms(1000);
	delay_ms(1000);
	createTcpOrUdp(TCP_SERVER, NULL, 0, 9000);
}

void STA_TCP_Client(void)
{
	setWifiMode(STA_MODE);
	delay_ms(1000);
	delay_ms(1000);
	delay_ms(1000);
	delay_ms(1000);
	delay_ms(1000);
	setConnectWifi(SSID, PASSWORD);
	delay_ms(1000);
	delay_ms(1000);
	delay_ms(1000);
	delay_ms(1000);
	delay_ms(1000);
	delay_ms(1000);
	delay_ms(1000);
	delay_ms(1000);
	delay_ms(1000);
	delay_ms(1000);
	createTcpOrUdp(TCP_CIENTS, REMOTEIP, 8080, 0);
	delay_ms(1000);
	delay_ms(1000);
	delay_ms(1000);
	delay_ms(1000);
	delay_ms(1000);
	setOSPF(1);
	delay_ms(1000);
	delay_ms(1000);
	delay_ms(1000);
	delay_ms(1000);
	delay_ms(1000);
	sendData(UDP, 0, 0);
}

