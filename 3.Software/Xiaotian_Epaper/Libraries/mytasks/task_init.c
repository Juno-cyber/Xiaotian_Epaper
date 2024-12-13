#include "myfreertos.h"


void init(){
	HAL_UART_Receive_IT(&huart2, rxBuffer, RTX_BUFFER_SIZE);		//开启串口接收中断
	init_run();														//更新时间
    init_show();													//Epaper显示
//	ds1032_init();				     								//ds1302初始化，设置好当前时间，烧录一次，然后注释掉再烧录一次就好了

    printf("task_init down!\n");
    osThreadSuspend(TASK_INITHandle);								//自杀初始化线程
}
