#include "myfreertos.h"

volatile int vc02_msg=0;												//外部输入指令值
TIMEData Time_start = {2023,6,18,12,0,0,7};					//正向计时事件，恋爱开始时间
TIMEData Time_haidilao;										//正向计时事件，海底捞冷却时间
TIMEData event_power[4];									//倒计时事件
char temp_itoa[6];											//用作数值转字符串的暂存数组
uint16_t temp_year=0;
uint8_t temp_month=0;
uint8_t temp_day=0;
uint8_t temp_hour=0;
uint8_t temp_minite=0;

void run() {
	update_run();
	osSemaphoreRelease(Binary_Sem_2Handle);
	osSemaphoreRelease(Binary_Sem_1Handle);
	osDelay(10);
}

// 判断是否是闰年

bool isLeapYear(uint16_t year) {
    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
        return true;
    }
    return false;
}

// 计算某年某月的天数
uint16_t daysInMonth(uint16_t year, uint16_t month) {
    switch (month) {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            return 31;
        case 4: case 6: case 9: case 11:
            return 30;
        case 2:
            return isLeapYear(year) ? 29 : 28;
        default:
            return 0; // 不会发生
    }
}

// 计算从基准日期（2000-01-01）到给定日期的天数
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

// 计算两个日期之间的天数差
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

void update_time()
{
	// 设置 date 字符串
	date[0] = (int8_t)(Time_now.year%100 / 10) + '0';
	date[1] = (int8_t)(Time_now.year%100 % 10) + '0';
	date[2] = '-';
	date[3] = (int8_t)(Time_now.month / 10) + '0';
	date[4] = (int8_t)(Time_now.month % 10) + '0';
	date[5] = '-';
	date[6] = (int8_t)(Time_now.day / 10) + '0';
	date[7] = (int8_t)(Time_now.day % 10) + '0';
	date[8] = '\0'; // 正确地在 date 字符串末尾添加终止符

	// 设置 time 字符串，注意这里不要修改 date 数组
	time[0] = (int8_t)(Time_now.hour / 10) + '0';
	time[1] = (int8_t)(Time_now.hour % 10) + '0';
	time[2] = ':';
	time[3] = (int8_t)(Time_now.minute / 10) + '0';
	time[4] = (int8_t)(Time_now.minute % 10) + '0';
	time[5] = '\0'; // 正确地在 time 字符串末尾添加终止符
}

void update_run()
{
	update_time();
	uint32_t temp_event=0;
	switch (vc02_msg) {
		case 1:					//切换灯光|切换背景主题

			break;
		case 2:					//完成日记了|写完日记了|写日记了
			event_power[0]=Time_now;
			osEventFlagsSet(Event_02Handle, 1<<0);
			break;
		case 3:					//完成阅读了|阅读了|看完书了
			event_power[1]=Time_now;
			osEventFlagsSet(Event_02Handle, 1<<0);
			break;
		case 4:					//完成浇花了|浇花了|浇水了
			event_power[3]=Time_now;
			osEventFlagsSet(Event_02Handle, 1<<0);
			break;
		case 5:					//坛子加水了|加水了|泡菜坛子
			event_power[2]=Time_now;
			osEventFlagsSet(Event_02Handle, 1<<0);
			break;
		case 6:					//海底捞了|吃了海底捞|海底捞
			Time_haidilao=Time_now;
			osEventFlagsSet(Event_02Handle, 1<<0);
			break;
		case 7:					//时间调整|时间更改|更改时间|调整时间

			break;
		case 8:					//时间年加一
			if((temp_time.year%100>=0)&&(temp_time.year%100<99))
			{
				temp_time.year += 1;
				osEventFlagsSet(Event_01Handle, 0x01<<0);
			}
			vc02_msg = 0;
			break;
		case 9:					//时间年减一
			if((temp_time.year%100>0)&&(temp_time.year%100<=99))
			{
				temp_time.year -= 1;
				osEventFlagsSet(Event_01Handle, 0x01<<0);
			}
			vc02_msg = 0;
			break;
		case 10:				//时间月加一
			if(temp_time.month>=0&&temp_time.month<12)
			{
				temp_time.month += 1;
				osEventFlagsSet(Event_01Handle, 0x01<<0);
			}
			vc02_msg = 0;
			break;
		case 11:				//时间月减一
			if(temp_time.month>0&&temp_time.month<=12)
			{
				temp_time.month -= 1;
				osEventFlagsSet(Event_01Handle, 0x01<<0);
			}
			vc02_msg = 0;
			break;
		case 12:				//时间日加一
			if(temp_time.day>=0&&temp_time.day<31)
			{
				temp_time.day += 1;
				osEventFlagsSet(Event_01Handle, 0x01<<0);
			}
			vc02_msg = 0;
			break;
		case 13:				//时间日减一
			if(temp_time.day>0&&temp_time.day<=31)
			{
				temp_time.day -= 1;
				osEventFlagsSet(Event_01Handle, 0x01<<0);
			}
			vc02_msg = 0;
			break;
		case 14:				//时间时加一
			if(temp_time.hour>=0&&temp_time.hour<23)
			{
				temp_time.hour += 1;
				osEventFlagsSet(Event_01Handle, 0x01<<0);
			}
			vc02_msg = 0;
			break;
		case 15:				//时间时减一
			if(temp_time.hour>0&&temp_time.hour<=23)
			{
				temp_time.hour -= 1;
				osEventFlagsSet(Event_01Handle, 0x01<<0);
			}
			vc02_msg = 0;
			break;
		case 16:				//时间分加一
			if(temp_time.minute>=0&&temp_time.minute<59)
			{
				temp_time.minute += 1;
				osEventFlagsSet(Event_01Handle, 0x01<<0);
			}
			vc02_msg = 0;
			break;
		case 17:				//时间分减一
			if(temp_time.minute>0&&temp_time.minute<=59)
			{
				temp_time.minute -= 1;
				osEventFlagsSet(Event_01Handle, 0x01<<0);
			}
			vc02_msg = 0;
			break;
		case 18:				//切换主图|更换图片|换个照片
			vc02_msg = 0;
			break;
		default:
			break;
	}
	if((temp_year != Time_now.year)||(temp_month != Time_now.month)||(temp_day != Time_now.day)||(temp_hour != Time_now.hour)||(temp_minite != Time_now.minute))
	{
		temp_year=Time_now.year;
		temp_month=Time_now.month;
		temp_day=Time_now.day;
		temp_hour=Time_now.hour;
		temp_minite=Time_now.minute;
		temp_time = Time_now;
		osEventFlagsSet(Event_02Handle, 1<<0);
		printf("更新显示！\n");
	}
	temp_event = osEventFlagsWait(Event_02Handle, 1<<0, osFlagsWaitAny, 0);	//等待显示事件位
	if(((temp_event&(1<<0))==(1<<0))&&((int)temp_event>0))
	{
		printf("Event_02 time:%d-%d-%d, %d:%d:%d \n",Time_now.year,Time_now.month,Time_now.day,Time_now.hour,Time_now.minute,Time_now.second);
		update_show();
	}

}

void init_run()
{
	while(Time_now.year==0)						//如果没有读到值就一直读
	{
		ds1032_read_realTime();
	}
	update_time();
	temp_time = Time_now;
	//正向计时事件
	Time_haidilao = Time_now;
	//倒计时事件
	for(int i=0;i<4;i++)
	{
		event_power[i]=Time_now;
	}
}



