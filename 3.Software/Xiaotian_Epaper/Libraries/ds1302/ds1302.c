#include "ds1302.h"
volatile TIMEData Time_now;
uint8_t read_time[7];

void ds1032_DATAOUT_init() //配置双向I/O端口为输出态
{
	GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	__HAL_RCC_GPIOB_CLK_ENABLE();
	/*Configure GPIO pin Output Level */
//	HAL_GPIO_WritePin(GPIOB, DS1302_DATA_Pin, GPIO_PIN_RESET);

	GPIO_InitStruct.Pin = DS1302_DATA_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}

void ds1032_DATAINPUT_init() //配置双向I/O端口为输入态
{
	GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	__HAL_RCC_GPIOB_CLK_ENABLE();
	GPIO_InitStruct.Pin = DS1302_DATA_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(DS1302_DATA_GPIO_Port, &GPIO_InitStruct);
}

void ds1302_write_onebyte(uint8_t data) //向DS1302发送一字节数据
{
	ds1032_DATAOUT_init();
	uint8_t count = 0;
	SCLK_L;
	for (count = 0; count < 8; count++) {
		SCLK_L;
		if (data & 0x01) {
			DATA_H;
		} else {
			DATA_L;
		} //先准备好数据再发送
		SCLK_H; //拉高时钟线，发送数据
		data >>= 1;
	}
}

void ds1302_wirte_rig(uint8_t address, uint8_t data) //向指定寄存器地址发送数据
{
	uint8_t temp1 = address;
	uint8_t temp2 = data;
	CE_L;
	SCLK_L;
	HAL_Delay(1);
	CE_H;
	HAL_Delay(2);
	ds1302_write_onebyte(temp1);
	ds1302_write_onebyte(temp2);
	CE_L;
	SCLK_L;
	HAL_Delay(2);
}

uint8_t ds1302_read_rig(uint8_t address) //从指定地址读取一字节数据
{
	uint8_t temp3 = address;
	uint8_t count = 0;
	uint8_t return_data = 0x00;
	CE_L;
	SCLK_L;
	HAL_Delay(3);
	CE_H;
	HAL_Delay(3);
	ds1302_write_onebyte(temp3);
	ds1032_DATAINPUT_init(); //配置I/O口为输入
	HAL_Delay(2);
	for (count = 0; count < 8; count++) {
		HAL_Delay(2); //使电平持续一段时间
		return_data >>= 1;
		SCLK_H;
		HAL_Delay(4); //使高电平持续一段时间
		SCLK_L;
		HAL_Delay(5); //延时14us后再去读取电压，更加准确
		if (HAL_GPIO_ReadPin(DS1302_DATA_GPIO_Port, DS1302_DATA_Pin)) {
			return_data = return_data | 0x80;
		}

	}
	HAL_Delay(2);
	CE_L;
	DATA_L;
	return return_data;
}

void ds1032_init() {

    // 解析日期
    int day, month, year;
    parse_date(COMPILE_DATE, &day, &month, &year);

    // 解析时间
    int hour, min, sec;
    parse_time(COMPILE_TIME, &hour, &min, &sec);

    if(Time_now.year!=year||Time_now.minute!=min){
    	//更新Time_now
    	Time_now.second = sec;
    	Time_now.minute = min;
    	Time_now.hour = hour;
    	Time_now.day = day;
    	Time_now.month = month;
    	Time_now.week = 7;
    	Time_now.year = year;
        // 转换数据格式
        uint8_t bcd_sec = int_to_bcd(sec);
        uint8_t bcd_min = int_to_bcd(min);
        uint8_t bcd_hour = int_to_bcd(hour);
        uint8_t bcd_day = int_to_bcd(day);
        uint8_t bcd_month = int_to_bcd(month);
        uint8_t bcd_year = int_to_bcd(year % 100); // 取年份后两位

        // 初始化DS1302
        ds1302_wirte_rig(0x8e, 0x00);  // 关闭写保护

        ds1302_wirte_rig(0x80, bcd_sec);    // 秒
        ds1302_wirte_rig(0x82, bcd_min);    // 分
        ds1302_wirte_rig(0x84, bcd_hour);   // 时（24小时制）
        ds1302_wirte_rig(0x86, bcd_day);    // 日
        ds1302_wirte_rig(0x88, bcd_month);  // 月
        ds1302_wirte_rig(0x8a, 0x07);       // 星期（需额外填入，这里使用日）
        ds1302_wirte_rig(0x8c, bcd_year);   // 年

        ds1302_wirte_rig(0x8e, 0x80);  // 启用写保护
    }

}

void ds1032_update(TIMEData time) {
	ds1302_wirte_rig(0x8e, 0x00); //关闭写保护
	ds1302_wirte_rig(0x80, int_to_bcd(time.second)); //seconds秒
	ds1302_wirte_rig(0x82, int_to_bcd(time.minute)); //minutes分
	ds1302_wirte_rig(0x84, int_to_bcd(time.hour)); //hours时
	ds1302_wirte_rig(0x86, int_to_bcd(time.day)); //date日
	ds1302_wirte_rig(0x88, int_to_bcd(time.month)); //months月
	ds1302_wirte_rig(0x8a, 0x07); //days
	ds1302_wirte_rig(0x8c, int_to_bcd(time.year%100)); //year年
	ds1302_wirte_rig(0x8e, 0x80); //关闭写保护
	HAL_Delay(10);
}

void ds1032_read_time() {
	read_time[0] = ds1302_read_rig(0x81); //读秒
	read_time[1] = ds1302_read_rig(0x83); //读分
	read_time[2] = ds1302_read_rig(0x85); //读时
	read_time[3] = ds1302_read_rig(0x87); //读日
	read_time[4] = ds1302_read_rig(0x89); //读月
	read_time[5] = ds1302_read_rig(0x8B); //读星期
	read_time[6] = ds1302_read_rig(0x8D); //读年
}

void ds1032_read_realTime() {
	ds1032_read_time();  //BCD码转换为10进制
	Time_now.second = (read_time[0] >> 4) * 10 + (read_time[0] & 0x0f);
	Time_now.minute = ((read_time[1] >> 4) & (0x07)) * 10
			+ (read_time[1] & 0x0f);
	Time_now.hour = (read_time[2] >> 4) * 10 + (read_time[2] & 0x0f);
	Time_now.day = (read_time[3] >> 4) * 10 + (read_time[3] & 0x0f);
	Time_now.month = (read_time[4] >> 4) * 10 + (read_time[4] & 0x0f);
	Time_now.week = read_time[5];
	Time_now.year = (read_time[6] >> 4) * 10 + (read_time[6] & 0x0f) + 2000;
}

uint8_t int_to_bcd(int num) {
    // 提取十位和个位
	uint8_t tens = num / 10;
	uint8_t units = num % 10;
    // 将十位和个位转换为4位BCD码并组合
    uint8_t bcd = (tens << 4) | units;
    return bcd;
}

// 月份字符串转数字的辅助函数
uint8_t month_str_to_num(const char* month) {
    const char* months[] = {"Jan","Feb","Mar","Apr","May","Jun",
                            "Jul","Aug","Sep","Oct","Nov","Dec"};
    for (int i = 0; i < 12; i++) {
        if (strncmp(month, months[i], 3) == 0) {
            return i + 1; // 月份从1开始
        }
    }
    return 1; // 默认1月
}

// 从日期字符串中提取日、月、年
void parse_date(const char* date_str, int* day, int* month, int* year) {
    char month_str[4];
    // 提取月份
    month_str[0] = date_str[0];
    month_str[1] = date_str[1];
    month_str[2] = date_str[2];
    month_str[3] = '\0';
    *month = month_str_to_num(month_str);

    // 提取日
    *day = (date_str[4] - '0') * 10 + (date_str[5] - '0');

    // 提取年
    *year = (date_str[7] - '0') * 1000 + (date_str[8] - '0') * 100 +
            (date_str[9] - '0') * 10 + (date_str[10] - '0');
}

// 从时间字符串中提取时、分、秒
void parse_time(const char* time_str, int* hour, int* min, int* sec) {
    *hour = (time_str[0] - '0') * 10 + (time_str[1] - '0');
    *min  = (time_str[3] - '0') * 10 + (time_str[4] - '0');
    *sec  = (time_str[6] - '0') * 10 + (time_str[7] - '0');
}
