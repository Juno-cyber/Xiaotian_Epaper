#include "myfreertos.h"

//��ʼ���߳�
void init(){
	HAL_UART_Receive_IT(&huart2, rxBuffer, RTX_BUFFER_SIZE);		//�������ڽ����ж�
	init_run();														//����ʱ��
	ds1032_init();				     								//ds1302��ʼ����������¼ʱ��������ʱ�����ڸ�ֵ��оƬʱ�䣬��������ˢ��
    init_show();													//Epaper��ʾ
    printf("��ʼ������!\n����ʱ��-��ǰʱ��= %d �� (������ʱ�䳬ǰ��ǰʱ���ǰʱ����ڱ���ʱ��20�������Ϊ����ʱ��)\n",temp_diff_min);
    osThreadSuspend(TASK_INITHandle);								//��ɱ��ʼ���߳�
}
