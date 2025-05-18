#ifndef __ds1302_H
#define __ds1302_H

#include "main.h"
#include <stdio.h>
#include <string.h>

// ʹ�ñ���ʱ�ĺ� __DATE__ �� __TIME__ ��ȡ����ʱ��
#define COMPILE_DATE __DATE__
#define COMPILE_TIME __TIME__


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
} TIMEData;//����TIMEData�ṹ�巽��洢ʱ����������

void ds1302_write_onebyte(uint8_t data);//��ds1302����һ�ֽ�����
void ds1302_wirte_rig(uint8_t address,uint8_t data);//��ָ���Ĵ���дһ�ֽ�����
uint8_t ds1302_read_rig(uint8_t address);//��ָ���Ĵ�����һ�ֽ�����
void ds1032_init();//ds1302��ʼ������
void ds1032_update(TIMEData time);
void ds1032_DATAOUT_init();//IO�˿�����Ϊ���
void ds1032_DATAINPUT_init();//IO�˿�����Ϊ����
void ds1032_read_time();//��ds1302��ȡʵʱʱ�䣨BCD�룩
void ds1032_read_realTime();//��BCD��ת��Ϊʮ��������
uint8_t int_to_bcd(int num);
uint8_t month_str_to_num(const char* month);
void parse_date(const char* date_str, int* day, int* month, int* year);
void parse_time(const char* time_str, int* hour, int* min, int* sec);
int64_t time_to_minutes(int year, int month, int day, int hour, int minute);
int64_t time_diff_minutes(
    int year1, int month1, int day1, int hour1, int minute1,
    int year2, int month2, int day2, int hour2, int minute2
);

extern volatile TIMEData Time_now;//ȫ�ֱ���

#endif
