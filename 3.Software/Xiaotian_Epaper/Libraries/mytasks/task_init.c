#include "myfreertos.h"

//初始化线程
void init(){
	HAL_UART_Receive_IT(&huart2, rxBuffer, RTX_BUFFER_SIZE);		//开启串口接收中断
	init_run();														//更新时间
	ds1032_init();				     								//ds1302初始化，初次烧录时，将编译时间日期赋值给芯片时间，后续不再刷新
    init_show();													//Epaper显示
    printf("初始化结束!\n编译时间-当前时间= %d 分 (若编译时间超前当前时间或当前时间大于编译时间20年则更新为编译时间)\n",temp_diff_min);
    osThreadSuspend(TASK_INITHandle);								//自杀初始化线程
}
