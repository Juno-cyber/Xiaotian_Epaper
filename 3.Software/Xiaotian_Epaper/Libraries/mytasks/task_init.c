#include "myfreertos.h"


void init(){
	HAL_UART_Receive_IT(&huart2, rxBuffer, RTX_BUFFER_SIZE);		//�������ڽ����ж�
	init_run();														//����ʱ��
    init_show();													//Epaper��ʾ
//	ds1032_init();				     								//ds1302��ʼ�������úõ�ǰʱ�䣬��¼һ�Σ�Ȼ��ע�͵�����¼һ�ξͺ���

    printf("task_init down!\n");
    osThreadSuspend(TASK_INITHandle);								//��ɱ��ʼ���߳�
}
