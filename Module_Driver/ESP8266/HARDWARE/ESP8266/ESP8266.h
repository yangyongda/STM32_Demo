#ifndef __ESP8266_H
#define __ESP8266_H
#include "sys.h"

#define CH_PD_PIN 						PCout(7)

#define SSID 									"yang"
#define PASSWORD							"y123456789"
#define REMOTEIP							"192.168.1.101"

//命令
#define MODULE_RESET					"AT+RST"
#define VERSION_INFO					"AT+GMR"
#define WIFI_MODE							"AT+CWMODE"
#define CONNECT_WIFI					"AT+CWJAP"
#define WIFI_LIST							"AT+CWLAP"
#define DISCONNECT_WIFI 			"AT+CWQAP"
#define CONNECT_STATUS				"AT+CIPSTATUS"
#define CREATE_TCP_UDP				"AT+CIPSTART"
#define SEND_DATA							"AT+CIPSEND"
#define CLOSE_TCP_UDP					"AT+CIPCLOSE"
#define GET_IP								"AT+CIFSR"
#define START_MUX_CONNECT			"AT+CIPMUX"
#define CONFIG_SERVER					"AT+CIPSERVER"
#define SET_MODULE_TRAN_MODE	"AT+CIPMODE"
#define SET_TIMEOUT						"AT+CIPSTO"
#define SET_AP_PARA						"AT+CWSAP"

//wifi模式
#define STA_MODE					1
#define AP_MODE						2
#define STA_AP_MODE				3

//通信类型
#define UDP					1
#define TCP_SERVER	2
#define TCP_CIENTS	3

void sendData(u8 type, u8 id, u16 num);
void initEsp8266(char* ssid, char* password);
void STA_UDP_Mode(void);
void STA_TCP_Server(void);
void STA_TCP_Client(void);

#endif

