#ifndef _OLED_H
#define _OLED_H

//y=0第一行，2第二行，4第三行，6第四行。
//x为0-127，数字字母x占8个点，汉字16个点。
#include "main.h"
#include "spi.h"
#define OLED1SPI 			hspi1
#define OLEDRST_PORT 	OLEDRES_GPIO_Port
#define OLEDRST_PIN 	OLEDRES_Pin
#define OLED1DC_PORT 	OLEDDC_GPIO_Port
#define OLED1DC_PIN 	OLEDDC_Pin
#define OLEDDAT 1
#define OLEDCMD 0
void OLED_Init(void);
void OLED1_Clear(void);//清屏
void OLED1_Display_On(void);//开显示
void OLED1_Display_Off(void);//关显示
void OLED1_ShowChar(uint8_t x,uint8_t y,char chr);//显示字符
void OLED1_ShowString(uint8_t x,uint8_t y,char *chr);//显示字符串
void OLED1_ShowNum(uint8_t x,uint8_t y,int32_t num,uint8_t len,uint8_t mode);//显示数字mode=1,补零，num有符号32位

#endif
