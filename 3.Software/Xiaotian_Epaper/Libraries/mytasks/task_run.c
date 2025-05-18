#include "myfreertos.h"

volatile int vc02_msg=0;												//�ⲿ����ָ��ֵ
TIMEData Time_start = {2023,6,18,12,0,0,7};					//�����ʱ�¼���������ʼʱ��
TIMEData Time_haidilao;										//�����ʱ�¼�����������ȴʱ��
TIMEData event_power[4];									//����ʱ�¼�
char temp_itoa[6];											//������ֵת�ַ������ݴ�����
volatile uint16_t temp_year=0;
volatile uint8_t temp_month=0;
volatile uint8_t temp_day=0;
volatile uint8_t temp_hour=0;
volatile uint8_t temp_minite=0;

void run() {
	update_run();
	osSemaphoreRelease(Binary_Sem_2Handle);
	osSemaphoreRelease(Binary_Sem_1Handle);
	osDelay(10);
}

// �ж��Ƿ�������

bool isLeapYear(uint16_t year) {
    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
        return true;
    }
    return false;
}

// ����ĳ��ĳ�µ�����
uint16_t daysInMonth(uint16_t year, uint16_t month) {
    switch (month) {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            return 31;
        case 4: case 6: case 9: case 11:
            return 30;
        case 2:
            return isLeapYear(year) ? 29 : 28;
        default:
            return 0; // ���ᷢ��
    }
}

// ����ӻ�׼���ڣ�2000-01-01�����������ڵ�����
uint16_t daysFromBase(uint16_t year, uint16_t month, uint16_t day) {
    uint16_t days = 0;
    for (uint16_t y = 2000; y < year; y++) {
        days += isLeapYear(y) ? 366 : 365;
    }
    for (uint16_t m = 1; m < month; m++) {
        days += daysInMonth(year, m);
    }
    days += day;
    return days;
}

// ������������֮���������
int date_diff(TIMEData time1,TIMEData time2) {
	if(time1.year!=0&&time2.year!=0)
	{
	    int days1 = daysFromBase(time1.year, time1.month, time1.day);
	    int days2 = daysFromBase(time2.year, time2.month, time2.day);
	    int temp = days2 - days1;
	    if (temp>0)
		{
	    	return temp;
		}
	    else {
			return 0;
		}

	}
	else {
		return 0;
	}
}

// �����2025��1��1�յ�����ʱ����ܷ�����
int64_t time_to_minutes(int year, int month, int day, int hour, int minute) {
	int64_t total_days = 0;

    // �����1970�굽(year-1)��������
    for (int y = 2000; y < year; y++) {
        total_days += isLeapYear(y) ? 366 : 365;
    }

    // ���㵱ǰ����·�����
    for (int m = 1; m < month; m++) {
        total_days += daysInMonth(year, m);
    }

    // ���ϵ�ǰ�µ�����
    total_days += day - 1;

    // ת��Ϊ����
    int64_t total_minutes = total_days * 24 * 60 + hour * 60 + minute;

    return total_minutes;
}

// ��������ʱ��ķ��Ӳ����ʱ�����ǰ�棬��ǰʱ����ں��棩
int64_t time_diff_minutes(
    int year1, int month1, int day1, int hour1, int minute1,
    int year2, int month2, int day2, int hour2, int minute2
) {
	int64_t t1 = time_to_minutes(year1, month1, day1, hour1, minute1);
	int64_t t2 = time_to_minutes(year2, month2, day2, hour2, minute2);
	if(t1>t2)
	{
		printf("����ʱ��>��ǰʱ�䣬����Ϊ����ʱ��\n");
	}
	else {
		printf("����ʱ��<��ǰʱ�䣬���ֵ�ǰʱ��\n");
	}
	return t1 - t2;
}

void update_time()
{
	// ���� date �ַ���
	date[0] = (int8_t)(Time_now.year%100 / 10) + '0';
	date[1] = (int8_t)(Time_now.year%100 % 10) + '0';
	date[2] = '-';
	date[3] = (int8_t)(Time_now.month / 10) + '0';
	date[4] = (int8_t)(Time_now.month % 10) + '0';
	date[5] = '-';
	date[6] = (int8_t)(Time_now.day / 10) + '0';
	date[7] = (int8_t)(Time_now.day % 10) + '0';
	date[8] = '\0'; // ��ȷ���� date �ַ���ĩβ�����ֹ��

	// ���� time �ַ�����ע�����ﲻҪ�޸� date ����
	time[0] = (int8_t)(Time_now.hour / 10) + '0';
	time[1] = (int8_t)(Time_now.hour % 10) + '0';
	time[2] = ':';
	time[3] = (int8_t)(Time_now.minute / 10) + '0';
	time[4] = (int8_t)(Time_now.minute % 10) + '0';
	time[5] = '\0'; // ��ȷ���� time �ַ���ĩβ�����ֹ��
}

void update_run()
{
	update_time();
	uint32_t temp_event=0;
	switch (vc02_msg) {
		case 1:					//�л��ƹ�|�л���������

			break;
		case 2:					//����ռ���|д���ռ���|д�ռ���
			event_power[0]=Time_now;
			osEventFlagsSet(Event_02Handle, 1<<0);
			break;
		case 3:					//����Ķ���|�Ķ���|��������
			event_power[1]=Time_now;
			osEventFlagsSet(Event_02Handle, 1<<0);
			break;
		case 4:					//��ɽ�����|������|��ˮ��
			event_power[3]=Time_now;
			osEventFlagsSet(Event_02Handle, 1<<0);
			break;
		case 5:					//̳�Ӽ�ˮ��|��ˮ��|�ݲ�̳��
			event_power[2]=Time_now;
			osEventFlagsSet(Event_02Handle, 1<<0);
			break;
		case 6:					//��������|���˺�����|������
			Time_haidilao=Time_now;
			osEventFlagsSet(Event_02Handle, 1<<0);
			break;
		case 7:					//ʱ�����|ʱ�����|����ʱ��|����ʱ��

			break;
		case 8:					//ʱ�����һ
			if((temp_time.year%100>=0)&&(temp_time.year%100<99))
			{
				temp_time.year += 1;
				osEventFlagsSet(Event_01Handle, 0x01<<0);
			}
			vc02_msg = 0;
			break;
		case 9:					//ʱ�����һ
			if((temp_time.year%100>0)&&(temp_time.year%100<=99))
			{
				temp_time.year -= 1;
				osEventFlagsSet(Event_01Handle, 0x01<<0);
			}
			vc02_msg = 0;
			break;
		case 10:				//ʱ���¼�һ
			if(temp_time.month>=0&&temp_time.month<12)
			{
				temp_time.month += 1;
				osEventFlagsSet(Event_01Handle, 0x01<<0);
			}
			vc02_msg = 0;
			break;
		case 11:				//ʱ���¼�һ
			if(temp_time.month>0&&temp_time.month<=12)
			{
				temp_time.month -= 1;
				osEventFlagsSet(Event_01Handle, 0x01<<0);
			}
			vc02_msg = 0;
			break;
		case 12:				//ʱ���ռ�һ
			if(temp_time.day>=0&&temp_time.day<31)
			{
				temp_time.day += 1;
				osEventFlagsSet(Event_01Handle, 0x01<<0);
			}
			vc02_msg = 0;
			break;
		case 13:				//ʱ���ռ�һ
			if(temp_time.day>0&&temp_time.day<=31)
			{
				temp_time.day -= 1;
				osEventFlagsSet(Event_01Handle, 0x01<<0);
			}
			vc02_msg = 0;
			break;
		case 14:				//ʱ��ʱ��һ
			if(temp_time.hour>=0&&temp_time.hour<23)
			{
				temp_time.hour += 1;
				osEventFlagsSet(Event_01Handle, 0x01<<0);
			}
			vc02_msg = 0;
			break;
		case 15:				//ʱ��ʱ��һ
			if(temp_time.hour>0&&temp_time.hour<=23)
			{
				temp_time.hour -= 1;
				osEventFlagsSet(Event_01Handle, 0x01<<0);
			}
			vc02_msg = 0;
			break;
		case 16:				//ʱ��ּ�һ
			if(temp_time.minute>=0&&temp_time.minute<59)
			{
				temp_time.minute += 1;
				osEventFlagsSet(Event_01Handle, 0x01<<0);
			}
			vc02_msg = 0;
			break;
		case 17:				//ʱ��ּ�һ
			if(temp_time.minute>0&&temp_time.minute<=59)
			{
				temp_time.minute -= 1;
				osEventFlagsSet(Event_01Handle, 0x01<<0);
			}
			vc02_msg = 0;
			break;
		case 18:				//�л���ͼ|����ͼƬ|������Ƭ
			vc02_msg = 0;
			break;
		default:
			break;
	}
//	printf("��ʱʱ��:%d-%d-%d,%d:%d \n",temp_year,temp_month,temp_day,temp_hour,temp_minite);
//	printf("���ڼ�ʱ: %d-%d-%d,%d:%d \n",Time_now.year,Time_now.month,Time_now.day,Time_now.hour,Time_now.minute);
	if((temp_year != Time_now.year)||(temp_month != Time_now.month)||(temp_day != Time_now.day)||(temp_hour != Time_now.hour)||(temp_minite != Time_now.minute))
	{
		temp_year=Time_now.year;
		temp_month=Time_now.month;
		temp_day=Time_now.day;
		temp_hour=Time_now.hour;
		temp_minite=Time_now.minute;
		temp_time = Time_now;
		osEventFlagsSet(Event_02Handle, 1<<0);
//		printf("������ʾ��\n");
	}
//	ʱ�䳬��Χ����
	if(Time_now.second>=60||Time_now.second<0)
	{
		temp_time.second = 0;
		osEventFlagsSet(Event_01Handle, 0x01<<0);
		printf("����ʱ���볬��������Χ!\n");
	}
	temp_event = osEventFlagsWait(Event_02Handle, 1<<0, osFlagsWaitAny, 0);	//�ȴ���ʾ�¼�λ
	if(((temp_event&(1<<0))==(1<<0))&&((int)temp_event>0))
	{
		printf("ʱ���Զ�����Event_02:%d-%d-%d, %d:%d \n",Time_now.year,Time_now.month,Time_now.day,Time_now.hour,Time_now.minute);
		update_show();
	}
}

void init_run()
{
    printf("�����������:%s ,�������ʱ��:%s \n",COMPILE_DATE,COMPILE_TIME);
	while(Time_now.year==0)						//���û�ж���ֵ��һֱ��
	{
		ds1032_read_realTime();
	}
	printf("��ǰʱ��:%d-%d-%d, %d:%d:%d \n",Time_now.year,Time_now.month,Time_now.day,Time_now.hour,Time_now.minute,Time_now.second);
	update_time();
	temp_time = Time_now;
	//�����ʱ�¼�
	Time_haidilao = Time_now;
	//����ʱ�¼�
	for(int i=0;i<4;i++)
	{
		event_power[i]=Time_now;
	}
}



