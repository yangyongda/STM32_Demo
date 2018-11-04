#include"lcd_ILI9325.h"
#include"delay.h"

void LCD_WR_REG(u16 index)
{
	*(__IO u16 *)(Bank1_LCD_C)=index;
}

void LCD_WR_Data(u16 val)
{
   *(__IO u16 *)(Bank1_LCD_D)=val;
}

void LCD_WR_CMD(u16 index,u16 val)
{
   *(__IO u16 *)(Bank1_LCD_C)=index;
   *(__IO u16 *)(Bank1_LCD_D)=val;
}


void ILI9325_Init(void)
{
	GPIO_ResetBits(GPIOE, GPIO_Pin_1);	  //硬件复位
	delay_ms(1);					   
	GPIO_SetBits(GPIOE, GPIO_Pin_1 );		 
	delay_ms(1);	
	
	LCD_WR_CMD(0x0001, 0x0100); // set SS and SM bit
	LCD_WR_CMD(0x0002, 0x0700); // set 1 line inversion
	LCD_WR_CMD(0x0003, 0x1030); // set GRAM write direction and BGR=1.
	LCD_WR_CMD(0x0004, 0x0000); // Resize register
	LCD_WR_CMD(0x0008, 0x0207); // set the back porch and front porch
	LCD_WR_CMD(0x0009, 0x0000); // set non-display area refresh cycle ISC[3:0]
	LCD_WR_CMD(0x000A, 0x0000); // FMARK function
	LCD_WR_CMD(0x000C, 0x0000); // RGB interface setting
	LCD_WR_CMD(0x000D, 0x0000); // Frame marker Position
	LCD_WR_CMD(0x000F, 0x0000); // RGB interface polarity
	
	LCD_WR_CMD(0x0010, 0x0000); // SAP, BT[3:0], AP, DSTB, SLP, STB
	LCD_WR_CMD(0x0011, 0x0007); // DC1[2:0], DC0[2:0], VC[2:0]
	LCD_WR_CMD(0x0012, 0x0000); // VREG1OUT voltage
	LCD_WR_CMD(0x0013, 0x0000); // VDV[4:0] for VCOM amplitude
	LCD_WR_CMD(0x0007, 0x0001);
	delay_ms(120); // Dis-charge capacitor power voltage
	LCD_WR_CMD(0x0010, 0x1490); // SAP, BT[3:0], AP, DSTB, SLP, STB
	LCD_WR_CMD(0x0011, 0x0227); // DC1[2:0], DC0[2:0], VC[2:0]
	delay_ms(50); // Delay 50ms
	LCD_WR_CMD(0x0012, 0x001C); // Internal reference voltage= Vci;
	delay_ms(50); // Delay 50ms
	LCD_WR_CMD(0x0013, 0x1A00); // Set VDV[4:0] for VCOM amplitude
	LCD_WR_CMD(0x0029, 0x0025); // Set VCM[5:0] for VCOMH
	LCD_WR_CMD(0x002B, 0x000C); // Set Frame Rate
	delay_ms(50); // Delay 50ms
	LCD_WR_CMD(0x0020, 0x0000); // GRAM horizontal Address
	LCD_WR_CMD(0x0021, 0x0000); // GRAM Vertical Address
	// ----------- Adjust the Gamma Curve ----------//
	LCD_WR_CMD(0x0030, 0x0000);
	LCD_WR_CMD(0x0031, 0x0506);
	LCD_WR_CMD(0x0032, 0x0104);
	LCD_WR_CMD(0x0035, 0x0207);
	LCD_WR_CMD(0x0036, 0x000F);
	LCD_WR_CMD(0x0037, 0x0306);
	LCD_WR_CMD(0x0038, 0x0102);
	LCD_WR_CMD(0x0039, 0x0707);
	LCD_WR_CMD(0x003C, 0x0702);
	LCD_WR_CMD(0x003D, 0x1604);
	//------------------ Set GRAM area ---------------//
	LCD_WR_CMD(0x0050, 0x0000); // Horizontal GRAM Start Address
	LCD_WR_CMD(0x0051, 0x00EF); // Horizontal GRAM End Address
	LCD_WR_CMD(0x0052, 0x0000); // Vertical GRAM Start Address
	LCD_WR_CMD(0x0053, 0x013F); // Vertical GRAM Start Address
	LCD_WR_CMD(0x0060, 0xA700); // Gate Scan Line
	LCD_WR_CMD(0x0061, 0x0001); // NDL,VLE, REV

	LCD_WR_CMD(0x006A, 0x0000); // set scrolling line
	//-------------- Partial Display Control ---------//
	LCD_WR_CMD(0x0080, 0x0000);
	LCD_WR_CMD(0x0081, 0x0000);
	LCD_WR_CMD(0x0082, 0x0000);
	LCD_WR_CMD(0x0083, 0x0000);
	LCD_WR_CMD(0x0084, 0x0000);			   
	LCD_WR_CMD(0x0085, 0x0000);
	//-------------- Panel Control -------------------//
	LCD_WR_CMD(0x0090, 0x0010);
	LCD_WR_CMD(0x0092, 0x0600);
	LCD_WR_CMD(0x0007, 0x0133); // 262K color and display ON	  
}

//指定位置画点（240*320）
void ILI_9325_Draw_Point(u8 x,u16 y,u16 color)
{
	//圈定一个矩形范围
	LCD_WR_CMD(0x50,x);	//x起始
	LCD_WR_CMD(0x51,x);	//x结束
	LCD_WR_CMD(0x52,y);	//y起始
	LCD_WR_CMD(0x53,y);	//y结束

	LCD_WR_CMD(0x20,x);//指定屏幕坐标	
	LCD_WR_CMD(0x21,y);
	LCD_WR_REG(0x22);  //写数据命令
	LCD_WR_Data(color);
}
//清屏函数
void ILI_9325_CLEAR(u16 color)
{
	u16 i=0,j=0;
	for(i=0;i<240;i++)
	{
		for(j=0;j<320;j++)
		{
			ILI_9325_Draw_Point(i,j,color);
		}
	}
}

/*
显示一个中文（24*24）
x--------显示位置的X坐标
y--------显示位置的Y坐标
foreColor-----字体颜色
backColoe------背景颜色
font-------要显示的字对应的字模数组
*/
void show_Chinese(u16 x, u16 y, u16 foreColor, u16 backColor, const u16 * font)
{
	u8 k=0,temp=0,t=0,y0=0;

	y0=y;//初值

	for(k=0;k<72;k++)  //72*8(一个字节) = 24*24  ，一个字节存储8个点
	{
		temp=font[k];
		for(t=0;t<8;t++)
		{
			if(temp&0x80)//该位为1则显示前景色
			 	ILI_9325_Draw_Point(x,y,foreColor);	
			else //否则显示背景色
				ILI_9325_Draw_Point(x,y,backColor);

			temp<<=1;
			y++;
			if((y-y0)==24) //一列总共24行，显示完一列后需要返回初始的y坐标，且x要向右移动
			{
				y=y0;
				x++;
				break;
			}
		}
	}
}

/*
显示一个中文字符串（24*24）
x--------显示位置的X坐标
y--------显示位置的Y坐标
foreColor-----字体颜色
backColoe------背景颜色
font-------要显示的字对应的字模数组
numByte------显示的字符数
*/
void show_ChineseStr(u16 x, u16 y, u16 foreColor, u16 backColor, const u16 font[][72], u16 numByte)
{
	u8 k=0,temp=0,t=0,y0=0,i=0;

	y0=y;//初值

	for(i=0; i<numByte ; i++)
	{
		for(k=0; k<72; k++)  //72*8(一个字节) = 24*24  ，一个字节存储8个点
		{
			temp=font[i][k];
			for(t=0;t<8;t++)
			{
				if(temp&0x80)//该位为1则显示前景色
				 	ILI_9325_Draw_Point(x,y,foreColor);	
				else //否则显示背景色
					ILI_9325_Draw_Point(x,y,backColor);
	
				temp<<=1;
				y++;
				if((y-y0)==24) //一列总共24行，显示完一列后需要返回初始的y坐标，且x要向右移动
				{
					y=y0;
					x++;
					break;
				}
			}
		}	
	}
	
}


/*
显示一个英文字符（12*24）
x--------显示位置的X坐标
y--------显示位置的Y坐标
foreColor-----字体颜色
backColoe------背景颜色
font-------要显示的字对应的字模数组
*/
void show_Char(u16 x ,u16 y, u16 foreColor, u16 backColor, const u16 * font)
{
	u8 k=0,temp=0,t=0,y0=0;

	y0=y;//初值

	for(k=0;k<36;k++) //36*8 = 12*24
	{
		temp=font[k];
		for(t=0;t<8;t++) //分别判断8个位(对应8个点)
		{
			if(temp&0x80)
			 	ILI_9325_Draw_Point(x,y,foreColor);
			else
				ILI_9325_Draw_Point(x,y,backColor);

			temp<<=1;
			y++;
			if((y-y0)==24)
			{
				y=y0;
				x++;
				break;
			}
		}
	}
}

/*
显示一个英文字符串（12*24）
x--------显示位置的X坐标
y--------显示位置的Y坐标
foreColor-----字体颜色
backColoe------背景颜色
font-------要显示的字对应的字模数组
numByte------显示的字符数
*/
void show_Str(u16 x ,u16 y, u16 foreColor, u16 backColor, const u16 font[][36], u16 numByte)
{
	u8 k=0,temp=0,t=0,y0=0 ,i =0;

	y0=y;//初值
	for(i=0; i<numByte ; i++)
	{
		for(k=0;k<36;k++) //36*8 = 12*24
		{
			temp=font[i][k];
			for(t=0;t<8;t++) //分别判断8个位(对应8个点)
			{
				if(temp&0x80)
				 	ILI_9325_Draw_Point(x,y,foreColor);
				else
					ILI_9325_Draw_Point(x,y,backColor);
	
				temp<<=1;
				y++;
				if((y-y0)==24)
				{
					y=y0;
					x++;
					break;
				}
			}
		}	
	}
	
}
/*
绘制一个矩形
x1------起始点的x坐标
y1------起始点的y坐标
x2------结束点的x坐标
y2------结束点的y坐标
color---绘制的颜色
*/
void Draw_Rectangle(u16 x1,u16 y1,u16 x2,u16 y2,u16 color)
{
	u16 i=0,j=0;

	for(i=x1;i<x2;i++)
	{
		for(j=y1;j<y2;j++)
		{
			ILI_9325_Draw_Point(i,j,color);
		}
	}
}
/*
另外一种绘制矩形的方法
x1------起始点的x坐标
y1------起始点的y坐标
x2------结束点的x坐标
y2------结束点的y坐标
color---绘制的颜色
*/
void Draw_Rect(u16 x1,u16 y1,u16 x2,u16 y2,u16 color)
{
	int i;
	//圈定一个矩形范围
	LCD_WR_CMD(0x50,x1);	//x起始
	LCD_WR_CMD(0x51,x2);	//x结束
	LCD_WR_CMD(0x52,y1);	//y起始
	LCD_WR_CMD(0x53,y2);	//y结束

	LCD_WR_CMD(0x20,x1);//指定屏幕坐标	
	LCD_WR_CMD(0x21,y1);
	LCD_WR_REG(0x22);  //写数据命令
	i = (x2-x1+1)*(y2-y1+1);
	while(i--)
	{
		LCD_WR_Data(color);
	}
}

void lcd_DrawPicture(u16 x,u16 y, u8 *pic)
{
  u32  i=8, len;
  u16 temp,width,height;
  	  

	
  width=((uint16_t)(pic[2]<<8)+pic[3])-1;	  	//图片长度
  height=((uint16_t)(pic[4]<<8)+pic[5])-1;	  	//图片高度
	
 	LCD_WR_CMD(0x50,x);					//x起始
	LCD_WR_CMD(0x51,x+width);		//x结束
	LCD_WR_CMD(0x52,y);					//y起始
	LCD_WR_CMD(0x53,y+height);	//y结束

	LCD_WR_CMD(0x20,x);//指定屏幕坐标	
	LCD_WR_CMD(0x21,y);
	LCD_WR_REG(0x22);  //写数据命令          	
 
  len=2*((uint16_t)(pic[2]<<8)+pic[3])*((uint16_t)(pic[4]<<8)+pic[5]);   //图片所占字节数
 
  while(i<(len+8)) {							 
  	temp=(uint16_t)( pic[i]<<8)+pic[i+1];		 
  	LCD_WR_Data(temp);				 
		i=i+2;						 
  }
}


void Lcd_init(void)
{
	FSMC_Init();   //FSMC初始化
	ILI9325_Init();	//ILI9325初始化
}

