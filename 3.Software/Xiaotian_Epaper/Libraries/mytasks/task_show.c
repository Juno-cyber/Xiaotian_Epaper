#include "myfreertos.h"

void show() {
	osSemaphoreAcquire(Binary_Sem_1Handle, osWaitForever);
	printf("当前时间:%d-%d-%d, %d:%d:%d \n",Time_now.year,Time_now.month,Time_now.day,Time_now.hour,Time_now.minute,Time_now.second);
//	HAL_GPIO_WritePin(IO_LED_GPIO_Port, IO_LED_Pin,
//			!HAL_GPIO_ReadPin(IO_LED_GPIO_Port, IO_LED_Pin));	//LED=0 亮
//	printf("vc02:%d\n",vc02_msg);
	osDelay(1000);
}

void init_show(){
	EPD_HW_Init(); 													//Electronic paper initialization

//	EPD_ALL_image(gImage1_white,gImage1_xiaowu);	//Refresh the picture in full screen

#ifdef scene1
#ifdef black_white_red
	EPD_WhiteScreen_Black();
#else
	EPD_WhiteScreen_White();
#endif

	EPD_W21_Init();
	//white
	EPD_Dis_Part(0, 0, gImage1_white, 296, 128, NEG);
	//right
	EPD_Dis_string(186, 0, time, 32, NEG);
	EPD_Dis_string(200, 32, date, 16, NEG);
	EPD_Dis_Part(210, 48, gImage_love, 32, 32, POS);
	EPD_Dis_string(210 + 32, 56, itoa(date_diff(Time_start, Time_now),temp_itoa,10), 16, NEG);
	EPD_Dis_Part(210, 80, gImage_haidi, 32, 32, NEG);
	EPD_Dis_string(210 + 32, 88, itoa(date_diff(Time_haidilao, Time_now),temp_itoa,10), 16, NEG);
	//middle
	EPD_Dis_Part(85, 0, photo1, 110, 128, POS);
	//	left
	EPD_Dis_power(0, 0, (date_diff(event_power[0], Time_now)>4)?0:4-date_diff(event_power[0], Time_now));
	EPD_Dis_power(0, 32, (date_diff(event_power[1], Time_now)>4)?0:4-date_diff(event_power[1], Time_now));
	EPD_Dis_power(0, 64, (date_diff(event_power[2], Time_now)>4)?0:4-date_diff(event_power[2], Time_now));
	EPD_Dis_power(0, 96, (date_diff(event_power[3], Time_now)>4)?0:4-date_diff(event_power[3], Time_now));
	EPD_Dis_Part(60, 0, gImage_riji, 32, 32, NEG);
	EPD_Dis_Part(60, 32, gImage_dushu, 32, 32, POS);
	EPD_Dis_Part(60, 64, gImage_tanzi, 32, 32, POS);
	EPD_Dis_Part(60, 96, gImage_jiaoshui, 32, 32, POS);
#endif

#ifdef scene2
#ifdef black_white_red
	EPD_WhiteScreen_Black();
#else
	EPD_WhiteScreen_White();
#endif
	EPD_W21_Init();
	//white
	EPD_Dis_Part(0, 0, gImage1_white, 296, 128, NEG);
	//	left
	EPD_Dis_Part(0, 0, gImage1_leju, 296, 128, POS);
	//right
	EPD_Dis_string(166, 0, time, 32, NEG);
	EPD_Dis_string(180, 32, date, 16, NEG);
	EPD_Dis_Part(190, 48, gImage_robot, 32, 32, POS);
	EPD_Dis_string(190 + 32, 56, itoa(date_diff(Time_start, Time_now),temp_itoa,10), 16, NEG);
	EPD_Dis_Part(190, 80, gImage_huoguo, 32, 32, POS);
	EPD_Dis_string(190 + 32, 88, itoa(date_diff(Time_haidilao, Time_now),temp_itoa,10), 16, NEG);
#endif

#ifdef scene3
#ifdef black_white_red
	EPD_WhiteScreen_Red();
#else
	EPD_WhiteScreen_White();
#endif
	EPD_W21_Init();

	EPD_ALL_image(gImage1_white,gImage1_xiaowu);
#endif
//
#ifdef scene4
#ifdef black_white_red
	EPD_WhiteScreen_Black();
#else
	EPD_WhiteScreen_White();
#endif
	EPD_W21_Init();
	//white
	EPD_Dis_Part(0, 0, gImage1_white, 296, 128, NEG);
	//	left
	EPD_Dis_Part(0, 0, qiegewala, 296, 128, POS);
	//right
	EPD_Dis_string(166, 0, time, 32, NEG);
	EPD_Dis_string(180, 32, date, 16, NEG);
	EPD_Dis_Part(190, 48, gImage_feizhou, 32, 32, POS);
	EPD_Dis_string(190 + 32, 56, itoa(date_diff(Time_start, Time_now),temp_itoa,10), 16, NEG);
	EPD_Dis_Part(190, 80, gImage_sport, 32, 32, POS);
	EPD_Dis_string(190 + 32, 88, itoa(date_diff(Time_haidilao, Time_now),temp_itoa,10), 16, NEG);
#endif
	EPD_Part_Update_and_DeepSleep();
}

void update_show()
{
	EPD_W21_Init();

#ifdef scene1
	//white
	EPD_Dis_Part(0, 0, gImage1_white, 296, 128, NEG);
	//right
	EPD_Dis_string(186, 0, time, 32, NEG);
	EPD_Dis_string(200, 32, date, 16, NEG);
	EPD_Dis_Part(210, 48, gImage_love, 32, 32, POS);
	EPD_Dis_string(210 + 32, 56, itoa(date_diff(Time_start, Time_now),temp_itoa,10), 16, NEG);
	EPD_Dis_Part(210, 80, gImage_haidi, 32, 32, NEG);
	EPD_Dis_string(210 + 32, 88, itoa(date_diff(Time_haidilao, Time_now),temp_itoa,10), 16, NEG);
	//middle
	EPD_Dis_Part(85, 0, photo1, 110, 128, POS);
	//	left
	EPD_Dis_power(0, 0, (date_diff(event_power[0], Time_now)>4)?0:4-date_diff(event_power[0], Time_now));
	EPD_Dis_power(0, 32, (date_diff(event_power[1], Time_now)>4)?0:4-date_diff(event_power[1], Time_now));
	EPD_Dis_power(0, 64, (date_diff(event_power[2], Time_now)>4)?0:4-date_diff(event_power[2], Time_now));
	EPD_Dis_power(0, 96, (date_diff(event_power[3], Time_now)>4)?0:4-date_diff(event_power[3], Time_now));
	EPD_Dis_Part(60, 0, gImage_riji, 32, 32, NEG);
	EPD_Dis_Part(60, 32, gImage_dushu, 32, 32, POS);
	EPD_Dis_Part(60, 64, gImage_tanzi, 32, 32, POS);
	EPD_Dis_Part(60, 96, gImage_jiaoshui, 32, 32, POS);
#endif

#ifdef scene2
	//white
	EPD_Dis_Part(0, 0, gImage1_white, 296, 128, NEG);
	//	left
	EPD_Dis_Part(0, 0, gImage1_leju, 296, 128, POS);
	//right
	EPD_Dis_string(166, 0, time, 32, NEG);
	EPD_Dis_string(180, 32, date, 16, NEG);
	EPD_Dis_Part(190, 48, gImage_robot, 32, 32, POS);
	EPD_Dis_string(190 + 32, 56, itoa(date_diff(Time_start, Time_now),temp_itoa,10), 16, NEG);
	EPD_Dis_Part(190, 80, gImage_huoguo, 32, 32, POS);
	EPD_Dis_string(190 + 32, 88, itoa(date_diff(Time_haidilao, Time_now),temp_itoa,10), 16, NEG);
#endif

#ifdef scene3

#endif

#ifdef scene4
	//white
	EPD_Dis_Part(0, 0, gImage1_white, 296, 128, NEG);
	//	left
	EPD_Dis_Part(0, 0, qiegewala, 296, 128, POS);
	//right
	EPD_Dis_string(166, 0, time, 32, NEG);
	EPD_Dis_string(180, 32, date, 16, NEG);
	EPD_Dis_Part(190, 48, gImage_feizhou, 32, 32, POS);
	EPD_Dis_string(190 + 32, 56, itoa(date_diff(Time_start, Time_now),temp_itoa,10), 16, NEG);
	EPD_Dis_Part(190, 80, gImage_sport, 32, 32, POS);
	EPD_Dis_string(190 + 32, 88, itoa(date_diff(Time_haidilao, Time_now),temp_itoa,10), 16, NEG);
#endif
	EPD_Part_Update_and_DeepSleep();
}





