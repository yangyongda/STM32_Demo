#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h"


#define KEY1  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_5)//��ȡ����1
#define KEY2  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_1)//��ȡ����2 



void KEY_Init(void);//IO��ʼ��
				    
#endif
