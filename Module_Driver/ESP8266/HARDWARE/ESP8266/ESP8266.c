#include "ESP8266.h"
#include "uart.h"
#include "delay.h"

/*
	复位模块 AT+RST
*/
void resetModule(void)
{
	char buffer[20];
	sprintf(buffer, "%s\r\n", (char*)MODULE_RESET);
	Uart2_Send_Buffer((u8*)buffer, 8);
}

/*
	SDK版本信息
*/
void getVersion(void)
{
	char buffer[20];
	sprintf(buffer, "%s\r\n", (char*)VERSION_INFO);
	Uart2_Send_Buffer((u8*)buffer, 8);
}

/*
函数功能:设置WIFI模式
参数说明: mode: 模式, 取值(1:STA, 2:AP 3:AP+STA)
*/
void setWifiMode(u8 mode)
{
	char buffer[20];
	sprintf(buffer, "%s=%d\r\n", (char*)WIFI_MODE, mode);
	Uart2_Send_Buffer((u8*)buffer, 13);
}

/*
函数功能: 连接路由器
参数说明: ssid: wifi名称
					password: wifi密码 
*/
void setConnectWifi(char* ssid, char* password)
{
	char buffer[60];
	sprintf(buffer, "%s=\"%s\",\"%s\"\r\n", (char*)CONNECT_WIFI, ssid, password);
	Uart2_Send_Buffer((u8*)buffer, 60);
}
/*
函数功能: 获取Wifi(AP)列表
*/
void getWifiList(void)
{
	char buffer[20];
	sprintf(buffer, "%s\r\n", (char*)WIFI_LIST);
	Uart2_Send_Buffer((u8*)buffer, 10);
}

/*
函数功能: 断开wifi连接
*/
void setDisConnectWifi(void)
{
	char buffer[20];
	sprintf(buffer, "%s\r\n", (char*)DISCONNECT_WIFI);
	Uart2_Send_Buffer((u8*)buffer, 10);
}

/*
函数功能:获取连接状态
*/
void getConnectStatus(void)
{
	char buffer[20];
	sprintf(buffer, "%s\r\n", (char*)CONNECT_STATUS);
	Uart2_Send_Buffer((u8*)buffer, 14);
}

/*
函数功能:创建TCP(client/server)/UDP
参数说明: type: 类型 1: UDP 2: TCP server 3: TCP client
					remoteIP: 远程IP
					remotePort: 远程端口
					localPort: 本地端口			
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
函数功能:设置透传模式
参数说明: mode: 1:透传模式  0:非透传模式
*/
void setOSPF(u8 mode)
{
	char buffer[20];
	sprintf(buffer, "%s=%d\r\n", (char*)SET_MODULE_TRAN_MODE, mode);
	Uart2_Send_Buffer((u8*)buffer, 14);
}

/*
函数功能:发送数据
参数说明: type: 类型 1: UDP 2: TCP server 3: TCP client
					id: TCP server多连接时使用的id号, 如果不是TCP Server就传0
					num:发送的字节数
注意: 如果id =0 num = 0则进入透传(前提是AT+CIPMODE=1)
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
函数功能:关闭TCP或UDP
*/
void closeTcpOrUdp(void)
{
	char buffer[20];
	sprintf(buffer, "%s\r\n", (char*)CLOSE_TCP_UDP);
	Uart2_Send_Buffer((u8*)buffer, 20);
}

/*
函数功能:获取IP地址
*/
void getIpAddress(void)
{
	char buffer[20];
	sprintf(buffer, "%s\r\n", (char*)GET_IP);
	Uart2_Send_Buffer((u8*)buffer, 20);
}

/*
函数功能:设置多连接
参数说明:mode: 0:单连接 1:多连接
*/
void setMuxConnect(u8 mode)
{
	char buffer[20];
	sprintf(buffer, "%s=%d\r\n", (char*)START_MUX_CONNECT, mode);
	Uart2_Send_Buffer((u8*)buffer, 20);
}

/*
函数功能:设置服务器断开连接超时时间
参数说明:timeout:超时时间
*/
void setConnectTimeOut(u16 timeout)
{
	char buffer[20];
	sprintf(buffer, "%s=%d\r\n", (char*)SET_TIMEOUT, timeout);
	Uart2_Send_Buffer((u8*)buffer, 20);
}
/*
函数功能: 设置AP参数
*/
void setAPPara(char* ssid, char* password, u8 channel, u8 encrypt)
{
	char buffer[60];
	sprintf(buffer, "%s=\"%s\",\"%s\",%d,%d\r\n", (char*)SET_AP_PARA, ssid, password, channel, encrypt);
	Uart2_Send_Buffer((u8*)buffer, 60);
}
	
void CH_PD_Init(void)
{
 
	GPIO_InitTypeDef  GPIO_InitStructure;	//GPIO配置结构体

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);	 //使能PB,PD端口时钟

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;				 			
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	GPIO_Init(GPIOC, &GPIO_InitStructure);					 		//根据设定参数初始化GPIOC.7
	GPIO_ResetBits(GPIOC,GPIO_Pin_7);						 				//PC.7 输出低

}

void initEsp8266(char* ssid, char* password)
{
	Uart2_Init();	//初始化串口
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

