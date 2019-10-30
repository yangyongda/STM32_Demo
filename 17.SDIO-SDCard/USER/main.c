#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "ff.h" 
#include "sdio_sdcard.h"
 
/************************************************
SDIO实验
FATFS管理SD卡
************************************************/

int res;   //读写文件的返回值
int a;

FIL fsrc,fdst;	//文件系统结构体，包含文件指针等成员
FATFS fs;		//记录文件系统盘符信息的结构体
TCHAR driNum = 0;
UINT br,bw;		//读写的字节数
BYTE buffer[512];  //缓存区
//BYTE textFileBuffer[]="欢迎来到STM32的世界！\r\n";
BYTE textFileBuffer[]="welcome to STM32\r\n";

int main(void)
{	
	delay_init();	    //延时函数初始化	  
	uart_init(115200);
	NVIC_Config();
	
	printf("\r\n Card init start\r\n");
	//0即为盘符
	f_mount(&fs, &driNum, 1);//创建工作区，调用了底层的disk_initialize()函数，进行SDIO接口初始化
	

	//以创建新文件或写入的方式打开盘符0下名为Demo.txt文件，不存在则创建
	//该文件和fsrc关联，通过该指针来操作文件
	res = f_open(&fdst, "0:/Demo1.txt",FA_CREATE_NEW | FA_WRITE);

	if(res == FR_OK)  //创建文件成功
	{
		res = f_write(&fdst, textFileBuffer, sizeof(textFileBuffer),&bw);
		printf("\r\n file create success \r\n");
		f_close(&fdst);
	}
	else if(res==FR_EXIST) //文件已经存在
	{
		printf("\r\n file exist \r\n");
	}
	
	//以只读的方式打开已经创建的文件
	res = f_open(&fdst, "0:/Demo1.txt", FA_OPEN_EXISTING | FA_READ);
	br=1;
	a=0;
	while(1)
	{
		for(a=0; a<512 ;a++)
		{
			buffer[a] = 0;//清空缓冲区
		}
		res = f_read(&fdst,buffer ,sizeof(buffer), &br);//将文件内容读到缓冲区
		printf("\r\n %s ",buffer);
		if(res || br ==0)
			break; //错误或到了文件尾
	}
	f_close(&fdst);	  //关闭打开的文件

	while(1);
}




