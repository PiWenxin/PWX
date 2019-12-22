#ifndef _OLED_H
#define _OLED_H

//y=0��һ�У�2�ڶ��У�4�����У�6�����С�
//xΪ0-127��������ĸxռ8���㣬����16���㡣
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
void OLED1_Clear(void);//����
void OLED1_Display_On(void);//����ʾ
void OLED1_Display_Off(void);//����ʾ
void OLED1_ShowChar(uint8_t x,uint8_t y,char chr);//��ʾ�ַ�
void OLED1_ShowString(uint8_t x,uint8_t y,char *chr);//��ʾ�ַ���
void OLED1_ShowNum(uint8_t x,uint8_t y,int32_t num,uint8_t len,uint8_t mode);//��ʾ����mode=1,���㣬num�з���32λ

#endif
