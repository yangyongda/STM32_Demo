#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "adc.h"
 
/************************************************
ADC实验

************************************************/


int main(void)
{	
	u16 adcx;
	float temp;
	
	delay_init();	    //延时函数初始化	  
	uart_init(115200); 	//初始化串口1
	Adc_Init();		//ADC初始化
	 
	while(1)
	{
		adcx=Get_Adc_Average(ADC_Channel_10,10);
		temp=(float)adcx*(3.3/4096);
		printf("ADC = %d, VOL = %f\r\n", adcx, temp);
		delay_ms(500);
	}
}



