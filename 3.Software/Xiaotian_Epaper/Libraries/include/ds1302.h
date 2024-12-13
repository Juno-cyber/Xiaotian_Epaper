#ifndef __ds1302_H
#define __ds1302_H

#include "main.h"
#include <stdio.h>

#define CE_L HAL_GPIO_WritePin(DS1302_CE_GPIO_Port,DS1302_CE_Pin,0)
#define CE_H HAL_GPIO_WritePin(DS1302_CE_GPIO_Port,DS1302_CE_Pin,1)
#define SCLK_L HAL_GPIO_WritePin(DS1302_SCL_GPIO_Port,DS1302_SCL_Pin,0)
#define SCLK_H HAL_GPIO_WritePin(DS1302_SCL_GPIO_Port,DS1302_SCL_Pin,1)
#define DATA_L HAL_GPIO_WritePin(DS1302_DATA_GPIO_Port,DS1302_DATA_Pin,0)
#define DATA_H HAL_GPIO_WritePin(DS1302_DATA_GPIO_Port,DS1302_DATA_Pin,1)

typedef struct
{
	uint16_t year;
	uint8_t  month;
	uint8_t  day;
	uint8_t  hour;
	uint8_t  minute;
	uint8_t  second;
	uint8_t  week;
} TIMEData;//创建TIMEData结构体方便存储时间日期数据

void ds1302_write_onebyte(uint8_t data);//向ds1302发送一字节数据
void ds1302_wirte_rig(uint8_t address,uint8_t data);//向指定寄存器写一字节数据
uint8_t ds1302_read_rig(uint8_t address);//从指定寄存器读一字节数据
void ds1032_init();//ds1302初始化函数
void ds1032_update(TIMEData time);
void ds1032_DATAOUT_init();//IO端口配置为输出
void ds1032_DATAINPUT_init();//IO端口配置为输入
void ds1032_read_time();//从ds1302读取实时时间（BCD码）
void ds1032_read_realTime();//将BCD码转化为十进制数据
uint8_t int_to_bcd(int num);


extern volatile TIMEData Time_now;//全局变量


#endif
