#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "adc.h"
#include "dac.h"
 
/************************************************
DACʵ��

��DACֵͨ��ADC��������
��PA4�ӵ�PC0
************************************************/


int main(void)
{	
	u16 dacValue = 0;
	u16 adcx;
	float temp;
	
	delay_init();	    //��ʱ������ʼ��	  
	uart_init(115200); 	//��ʼ������1
	Adc_Init();		//ADC��ʼ��
	Dac1_Init();	//DAC��ʼ��
	 
	while(1)
	{
		Dac1_Set_Vol(dacValue);
		adcx=Get_Adc_Average(ADC_Channel_10,10);
		temp=(float)adcx*(3.3/4096);
		printf("setDAC = %d, ADC = %d, VOL = %f\r\n",dacValue, adcx, temp);
		delay_ms(1000);
		dacValue += 100;
		if(dacValue > 4095)
		{
			dacValue = 0;
		}
	}
}



