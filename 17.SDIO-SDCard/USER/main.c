#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "ff.h" 
#include "sdio_sdcard.h"
 
/************************************************
SDIOʵ��
FATFS����SD��
************************************************/

int res;   //��д�ļ��ķ���ֵ
int a;

FIL fsrc,fdst;	//�ļ�ϵͳ�ṹ�壬�����ļ�ָ��ȳ�Ա
FATFS fs;		//��¼�ļ�ϵͳ�̷���Ϣ�Ľṹ��
TCHAR driNum = 0;
UINT br,bw;		//��д���ֽ���
BYTE buffer[512];  //������
//BYTE textFileBuffer[]="��ӭ����STM32�����磡\r\n";
BYTE textFileBuffer[]="welcome to STM32\r\n";

int main(void)
{	
	delay_init();	    //��ʱ������ʼ��	  
	uart_init(115200);
	NVIC_Config();
	
	printf("\r\n Card init start�\\r\n");
	//0��Ϊ�̷�
	f_mount(&fs, &driNum, 1);//�����������������˵ײ��disk_initialize()����������SDIO�ӿڳ�ʼ��
	

	//�Դ������ļ���д��ķ�ʽ���̷�0����ΪDemo.txt�ļ����������򴴽�
	//���ļ���fsrc������ͨ����ָ���������ļ�
	res = f_open(&fdst, "0:/Demo1.txt",FA_CREATE_NEW | FA_WRITE);

	if(res == FR_OK)  //�����ļ��ɹ�
	{
		res = f_write(&fdst, textFileBuffer, sizeof(textFileBuffer),&bw);
		printf("\r\n file create success \r\n");
		f_close(&fdst);
	}
	else if(res==FR_EXIST) //�ļ��Ѿ�����
	{
		printf("\r\n file exist \r\n");
	}
	
	//��ֻ���ķ�ʽ���Ѿ��������ļ�
	res = f_open(&fdst, "0:/Demo1.txt", FA_OPEN_EXISTING | FA_READ);
	br=1;
	a=0;
	while(1)
	{
		for(a=0; a<512 ;a++)
		{
			buffer[a] = 0;//��ջ�����
		}
		res = f_read(&fdst,buffer ,sizeof(buffer), &br);//���ļ����ݶ���������
		printf("\r\n %s ",buffer);
		if(res || br ==0)
			break; //��������ļ�β
	}
	f_close(&fdst);	  //�رմ򿪵��ļ�

	while(1);
}




