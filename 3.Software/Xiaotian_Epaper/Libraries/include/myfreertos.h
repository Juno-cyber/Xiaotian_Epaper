#ifndef __MYFREERTOS_H
#define __MYFREERTOS_H

#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"
#include "cmsis_os2.h"
#include <stdlib.h>
#include "EPAPER.h"
#include "myusart.h"
#include "ds1302.h"

#define RTX_BUFFER_SIZE 1
// ���Բο������Լ��ĳ���
#define scene1						//��ʾ����1
//#define scene2						//��ʾ����2

typedef enum { false, true } bool; // �Զ���bool���ͺͳ���

//��ʾ����
void show();
void init_show();
void update_show();


//���и�������
void run();
bool isLeapYear(uint16_t year);
uint16_t daysInMonth(uint16_t year, uint16_t month);
uint16_t daysFromBase(uint16_t year, uint16_t month, uint16_t day);
int date_diff(TIMEData time1,TIMEData time2);
void update_time();
void update_run();
void init_run();

//ͨ�Ŷ�ȡ����
void read();

//��ʼ������
void init();

extern osSemaphoreId Binary_Sem_1Handle;
extern osSemaphoreId Binary_Sem_2Handle;
extern osThreadId TASK_INITHandle;
extern UART_HandleTypeDef huart2;
extern osEventFlagsId_t Event_01Handle;
extern osEventFlagsId_t Event_02Handle;

extern uint8_t txBuffer[RTX_BUFFER_SIZE];
extern uint8_t rxBuffer[RTX_BUFFER_SIZE];
extern volatile int vc02_msg;
extern char date[9];
extern char time[6];
extern TIMEData Time_start;
extern TIMEData Time_haidilao;
extern char temp_itoa[6];
extern TIMEData event_power[4];
extern volatile TIMEData temp_time;

#endif
