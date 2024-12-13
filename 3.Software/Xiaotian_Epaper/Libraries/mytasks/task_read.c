#include "myfreertos.h"

uint8_t txBuffer[RTX_BUFFER_SIZE];
uint8_t rxBuffer[RTX_BUFFER_SIZE];
char date[9];
char time[6];
volatile TIMEData temp_time;


void read() {
	osSemaphoreAcquire(Binary_Sem_2Handle, osWaitForever);
	uint32_t temp_event1=0;
	if (rxBuffer[0] != 0) { // ����Ƿ������ݽ���
		printf("receive: %d\n",rxBuffer[0]);
		vc02_msg = rxBuffer[0];
		for(int i=0;i<RTX_BUFFER_SIZE;i++)
		{
			rxBuffer[i]=0;
		}
	}
	temp_event1 = osEventFlagsWait(Event_01Handle, 1<<0, osFlagsWaitAny, 0);
	printf("read!...\n");
	if(((temp_event1&(0x01<<0))==1)&&((int)temp_event1>0))
	{
		printf("Event_01 :%d-%d-%d, %d:%d:%d \n",temp_time.year,temp_time.month,temp_time.day,temp_time.hour,temp_time.minute,temp_time.second);
		ds1032_update(temp_time);
//		ds1032_read_realTime();         //��ȡʵʱ����
//		osEventFlagsSet(Event_02Handle, 1<<0);		//��λ ��ʾ�¼�λ
	}
	ds1032_read_realTime();         //��ȡʵʱ����
	osDelay(10);
}







