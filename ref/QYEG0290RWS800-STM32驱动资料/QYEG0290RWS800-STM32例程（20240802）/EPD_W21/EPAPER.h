#ifndef __EPAPER_H
#define __EPAPER_H
#include "stm32f10x.h"
//296*128///////////////////////////////////////

#define Hor 1 				//FCP����ߣFPC is located on the left side��
#define Ver 2					//FPC���±ߣ�FPC located below��

//�ɱ���ʾԪ����ʾ����

#define W_digit 24		//���ֵĿ�*��=24*40
#define H_digit 40 
#define W_dot 12			//С����Ŀ��=12


//�ɱ���ʾԪ������
#define x_digit_1		  35										//��һλ���ֵ�x����
#define y_digit 			56										//���ֵ�y����



//������ʾ����
#define EPD_HEIGHT 128
#define EPD_WIDTH  296

#define ALLSCREEN_GRAGHBYTES	EPD_WIDTH*EPD_HEIGHT/8

///////////////////////////GPIO Settings//////////////////////////////////////////////////////

#define EPD_W21_MOSI_0	GPIO_ResetBits(GPIOD, GPIO_Pin_10)
#define EPD_W21_MOSI_1	GPIO_SetBits(GPIOD, GPIO_Pin_10)

#define EPD_W21_CLK_0	GPIO_ResetBits(GPIOD, GPIO_Pin_9)
#define EPD_W21_CLK_1	GPIO_SetBits(GPIOD, GPIO_Pin_9)

#define EPD_W21_CS_0	GPIO_ResetBits(GPIOD, GPIO_Pin_8)
#define EPD_W21_CS_1	GPIO_SetBits(GPIOD, GPIO_Pin_8)

#define EPD_W21_DC_0	GPIO_ResetBits(GPIOE, GPIO_Pin_15)
#define EPD_W21_DC_1	GPIO_SetBits(GPIOE, GPIO_Pin_15)

#define EPD_W21_RST_0	GPIO_ResetBits(GPIOE, GPIO_Pin_14)
#define EPD_W21_RST_1	GPIO_SetBits(GPIOE, GPIO_Pin_14)

#define EPD_W21_BUSY_LEVEL 0
#define isEPD_W21_BUSY GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_13) 


void driver_delay_xms(unsigned long xms);			
void EpaperIO_Init(void);
void Epaper_READBUSY(void);
void Epaper_Spi_WriteByte(unsigned char TxData);
void Epaper_Write_Command(unsigned char cmd);
void Epaper_Write_Data(unsigned char data);

void EPD_HW_Init(unsigned char direction); //Electronic paper initialization
void EPD_W21_Init(void); //Electronic paper hard reset

void EPD_Update_BaseMap(void);
void EPD_Update_And_DeepSleep(void);
void EPD_Part_Update_And_DeepSleep(void); 
	
//Display 

void EPD_WhiteScreen_Red(void);
void EPD_WhiteScreen_Black(void);
void EPD_WhiteScreen_White(void);

void EPD_ALL_image(const unsigned char *datas_BW,const unsigned char *datas_RW);
void EPD_SetRAMValue_BaseMap(const unsigned char *datas_BW,const unsigned char *datas_RED);
void EPD_multiple_Part(int h_start,int v_start,const unsigned char * digit_1,const unsigned char * digit_2,const unsigned char * digit_3,const unsigned char * digit_4);

#endif


