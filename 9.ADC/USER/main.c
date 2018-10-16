#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "adc.h"
 
/************************************************
ADCʵ��

************************************************/


int main(void)
{	
	u16 adcx;
	float temp;
	
	delay_init();	    //��ʱ������ʼ��	  
	uart_init(115200); 	//��ʼ������1
	Adc_Init();		//ADC��ʼ��
	 
	while(1)
	{
		adcx=Get_Adc_Average(ADC_Channel_10,10);
		temp=(float)adcx*(3.3/4096);
		printf("ADC = %d, VOL = %f\r\n", adcx, temp);
		delay_ms(500);
	}
}



