#ifndef __EPAPER_H
#define __EPAPER_H
#include "main.h"
#include <stdio.h>
//296*128///////////////////////////////////////

#define POS 1
#define NEG 2 
#define OFF 3 


#define EPD_WIDTH  296
#define EPD_HEIGHT 128

#define ALLSCREEN_GRAGHBYTES	EPD_WIDTH*EPD_HEIGHT/8
//选择屏幕类型，共适配了两种类型的显示屏，bom表中有列出链接，可以根据自己选择来做选择
#define black_white_red	//使用黑白红墨水屏
//#define black_white			//使用黑白墨水屏

///////////////////////////GPIO Settings//////////////////////////////////////////////////////

#define EPD_W21_MOSI_0	HAL_GPIO_WritePin(EP_SDI_GPIO_Port, EP_SDI_Pin, 0)
#define EPD_W21_MOSI_1	HAL_GPIO_WritePin(EP_SDI_GPIO_Port, EP_SDI_Pin, 1)

#define EPD_W21_CLK_0	HAL_GPIO_WritePin(EP_SCK_GPIO_Port, EP_SCK_Pin, 0)
#define EPD_W21_CLK_1	HAL_GPIO_WritePin(EP_SCK_GPIO_Port, EP_SCK_Pin, 1)

#define EPD_W21_CS_0	HAL_GPIO_WritePin(EP_CS_GPIO_Port, EP_CS_Pin, 0)
#define EPD_W21_CS_1	HAL_GPIO_WritePin(EP_CS_GPIO_Port, EP_CS_Pin, 1)

#define EPD_W21_DC_0	HAL_GPIO_WritePin(EP_DC_GPIO_Port, EP_DC_Pin, 0)
#define EPD_W21_DC_1	HAL_GPIO_WritePin(EP_DC_GPIO_Port, EP_DC_Pin, 1)

#define EPD_W21_RST_0	HAL_GPIO_WritePin(EP_RST_GPIO_Port, EP_RST_Pin, 0)
#define EPD_W21_RST_1	HAL_GPIO_WritePin(EP_RST_GPIO_Port, EP_RST_Pin, 1)

#define EPD_W21_BUSY_LEVEL 0			//BUSY引脚初始下拉
#define isEPD_W21_BUSY HAL_GPIO_ReadPin(EP_BUSY_GPIO_Port, EP_BUSY_Pin)


//void EpaperIO_Init(void);
void Epaper_READBUSY(void);
void Epaper_Spi_WriteByte(unsigned char TxData);
void Epaper_Write_Command(unsigned char cmd);
void Epaper_Write_Data(unsigned char data);

void EPD_HW_Init_4GRAY(void);			//Electronic paper initialization锟斤拷4锟揭阶ｏ拷
void EPD_HW_Init(void); //Electronic paper initialization
void EPD_W21_Init(void); //Electronic paper hard reset
void EPD_Update_and_DeepSleep(void);
void EPD_Update_4GRAY_and_DeepSleep(void);


#ifdef black_white_red
//可变显示元素显示区域
#define W_digit 24		//数字的宽*高=24*40
#define H_digit 40
#define W_dot 12			//小数点的宽度=12
//可变显示元素坐标
#define x_digit_1		  35										//第一位数字的x坐标
#define y_digit 			56										//数字的y坐标
//整屏显示区域
#define EPD_HEIGHT 128
#define EPD_WIDTH  296

void EPD_WhiteScreen_Red(void);
void EPD_WhiteScreen_Black(void);
void EPD_WhiteScreen_White(void);
void EPD_Update_and_DeepSleep(void);
void EPD_Part_Update_and_DeepSleep(void);
void EPD_Update_BaseMap(void);

void EPD_ALL_image(const unsigned char *datas_BW,const unsigned char *datas_RW);
void EPD_SetRAMValue_BaseMap(const unsigned char *datas_BW,const unsigned char *datas_RED);
void EPD_multiple_Part(int h_start,int v_start,const unsigned char * digit_1,const unsigned char * digit_2,const unsigned char * digit_3,const unsigned char * digit_4);

#endif

#ifdef black_white

void EPD_SetRAMValue_BaseMap(const unsigned char * datas);
void EPD_WhiteScreen_White(void);
void EPD_Part_Update_and_DeepSleep(void);
#endif

//Display 
void EPD_WhiteScreen_ALL_4GRAY(const unsigned char *datas);
void EPD_WhiteScreen_ALL(const unsigned char *datas);

void EPD_Dis_Part(int h_start,int v_start,const unsigned char * datas,int PART_WIDTH,int PART_HEIGHT,unsigned char mode);

//Display easy
void EPD_Dis_ascii(int h_start,int v_start,char ascii,int size,unsigned char mode);
void EPD_Dis_ascii_short(int h_start,int v_start,char ascii,int size,unsigned char mode);
void EPD_Dis_string(int h_start,int v_start,const char *str,int size,unsigned char mode);
void EPD_run_length_decode(const unsigned char *ascii,unsigned char *font_out,char charr,int size);
void EPD_Dis_power(int h_start, int v_start, int power);

//array extern
//font
extern const unsigned char ascii_16_short[1933];
extern const unsigned char ascii_32_short[6227];
//pic
extern const unsigned char gImage_haidi[128];
extern const unsigned char gImage_love[128];
extern const unsigned char gImage_square[885];
extern const unsigned char gImage_tanzi[128];
extern const unsigned char gImage_jiaoshui[128];
extern const unsigned char gImage_dushu[128];
extern const unsigned char gImage_riji[128];
extern const unsigned char gImage_huoguo[128];
extern const unsigned char gImage_feizhou[128];
extern const unsigned char gImage_sport[128];
extern const unsigned char photo1[1760];
extern const unsigned char photo2[1760];
extern const unsigned char qiegewala[4736];
extern const unsigned char photo3[2400];
extern const unsigned char gImage1_xiaowu[4736];
extern const unsigned char gImage1_white[4736];

#endif


