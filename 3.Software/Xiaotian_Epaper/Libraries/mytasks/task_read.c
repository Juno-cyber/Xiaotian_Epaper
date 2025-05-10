#include "myfreertos.h"

uint8_t txBuffer[RTX_BUFFER_SIZE];
uint8_t rxBuffer[RTX_BUFFER_SIZE];
char date[9];
char time[6];
volatile TIMEData temp_time;


void read() {
	osSemaphoreAcquire(Binary_Sem_2Handle, osWaitForever);
	uint32_t temp_event1=0;
	if (rxBuffer[0] != 0) { // 检查是否有数据接收
		printf("接收指令代码: %d\n",rxBuffer[0]);
		vc02_msg = rxBuffer[0];
		for(int i=0;i<RTX_BUFFER_SIZE;i++)
		{
			rxBuffer[i]=0;
		}
	}
	temp_event1 = osEventFlagsWait(Event_01Handle, 1<<0, osFlagsWaitAny, 0);
//	printf("read!...\n");
	if(((temp_event1&(0x01<<0))==1)&&((int)temp_event1>0))
	{
		printf("时间人为更新Event_01 :%d-%d-%d, %d:%d \n",temp_time.year,temp_time.month,temp_time.day,temp_time.hour,temp_time.minute);
		ds1032_update(temp_time);
//		ds1032_read_realTime();         //读取实时数据
//		osEventFlagsSet(Event_02Handle, 1<<0);		//置位 显示事件位
	}
	ds1032_read_realTime();         //读取实时数据
	osDelay(10);
}







