#include<oled.h>
#include<oledfont.h>

const uint8_t oledinitcode[30]={0xAE,0X00,0X10,0X40,0X81,0XCF,0XA1,0XC8,0XA6,0XA8,
														0X3F,0XD3,0X00,0XD5,0X80,0XD9,0XF1,0XDA,0X12,0XDB,
														0X40,0X20,0X02,0X8D,0X14,0XA4,0XA6,0XAF,0XAF};

void oled1_wr_byte(uint8_t data,uint8_t mode)
{
	if(mode==OLEDDAT)
		HAL_GPIO_WritePin(OLED1DC_PORT,OLED1DC_PIN,GPIO_PIN_SET);
	else
		HAL_GPIO_WritePin(OLED1DC_PORT,OLED1DC_PIN,GPIO_PIN_RESET);
	HAL_SPI_Transmit(&OLED1SPI,&data,1,1);
}

void OLED1_Clear(void)
{
	uint8_t i,n;		    
	for(i=0;i<8;i++)  
	{  
		oled1_wr_byte(0xb0+i,OLEDCMD);    //设置页地址（0~7）
		oled1_wr_byte(0x00,OLEDCMD);      //设置显示位置—列低地址
		oled1_wr_byte(0x10,OLEDCMD);      //设置显示位置—列高地址   
		for(n=0;n<128;n++)
			oled1_wr_byte(0,OLEDDAT); 
	}
}

void OLED1_Set_Pos(uint8_t x,uint8_t y) 
{ 
	oled1_wr_byte(0xb0+y,OLEDCMD);
	oled1_wr_byte(((x&0xf0)>>4)|0x10,OLEDCMD);
	oled1_wr_byte((x&0x0f)|0x01,OLEDCMD); 
}

void OLED_Init(void)
{
	HAL_GPIO_WritePin(OLEDRST_PORT,OLEDRST_PIN,GPIO_PIN_SET);
	HAL_Delay(100);
	HAL_GPIO_WritePin(OLEDRST_PORT,OLEDRST_PIN,GPIO_PIN_RESET);
	HAL_Delay(100);
	HAL_GPIO_WritePin(OLEDRST_PORT,OLEDRST_PIN,GPIO_PIN_SET);
	
	HAL_GPIO_WritePin(OLED1DC_PORT,OLED1DC_PIN,GPIO_PIN_RESET);
	HAL_SPI_Transmit(&OLED1SPI,(uint8_t *)oledinitcode,29,100);
	
	OLED1_Clear();
	OLED1_Set_Pos(0,0);
	OLED1_Clear();
}

void OLED1_Display_On(void)
{
	oled1_wr_byte(0X8D,OLEDCMD);  //SET DCDC命令
	oled1_wr_byte(0X14,OLEDCMD);  //DCDC ON
	oled1_wr_byte(0XAF,OLEDCMD);  //DISPLAY ON
}

void OLED1_Display_Off(void)
{
	oled1_wr_byte(0X8D,OLEDCMD);  //SET DCDC命令
	oled1_wr_byte(0X10,OLEDCMD);  //DCDC OFF
	oled1_wr_byte(0XAE,OLEDCMD);  //DISPLAY OFF
}

void OLED1_ShowChar(uint8_t x,uint8_t y,char chr)
{      	
	uint8_t c=0,i=0;	
	c=chr-' ';//得到偏移后的值			
	if(x>127)
	{
		x=0;
		y=y+2;
	}
	OLED1_Set_Pos(x,y);	
	for(i=0;i<8;i++)
		oled1_wr_byte(F8X16[c*16+i],OLEDDAT);
	OLED1_Set_Pos(x,y+1);
	for(i=0;i<8;i++)
		oled1_wr_byte(F8X16[c*16+i+8],OLEDDAT);
}

void OLED1_ShowString(uint8_t x,uint8_t y,char *chr)
{
	unsigned char j=0;
	while (chr[j]!='\0')
	{		
		OLED1_ShowChar(x,y,chr[j]);
		x+=8;
		if(x>120){x=0;y+=2;}
			j++;
	}
}

//m^n函数
uint32_t oled_pow(uint8_t m,uint8_t n)
{
	uint32_t result=1;	 
	while(n--)
		result*=m;    
	return result;
}		

//x,y :起点坐标	 
//len :数字的位数
//mode:1补零，0不补
//num:数值有符号32位;	 		  
void OLED1_ShowNum(uint8_t x,uint8_t y,int32_t num,uint8_t len,uint8_t mode)
{         	
	uint8_t t,temp;
	uint8_t enshow=0;
	if(num<0)
	{
		OLED1_ShowChar(x,y,'-');
		len--;
		x+=8;
		num=-num;
		for(t=0;t<len;t++)
		{
			temp=(num/oled_pow(10,len-t-1))%10;
			if(enshow==0&&t<(len-1))
			{
				if(temp==0)
				{
					if(mode==0)
						OLED1_ShowChar(x+8*t,y,' ');
					else
						OLED1_ShowChar(x+8*t,y,'0');
					continue;
				}
				else 
					enshow=1; 
			}
			OLED1_ShowChar(x+8*t,y,temp+'0'); 
		}
	}
	else
	{
		for(t=0;t<len;t++)
		{
			temp=(num/oled_pow(10,len-t-1))%10;
			if(enshow==0&&t<(len-1))
			{
				if(temp==0)
				{
					if(mode==0)
						OLED1_ShowChar(x+8*t,y,' ');
					else
						OLED1_ShowChar(x+8*t,y,'0');
					continue;
				}
				else 
					enshow=1; 
			}
			OLED1_ShowChar(x+8*t,y,temp+'0'); 
		}
	}
}
