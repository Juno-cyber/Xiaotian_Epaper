#include "ds1302.h"
volatile TIMEData Time_now;
uint8_t read_time[7];

void ds1032_DATAOUT_init() //����˫��I/O�˿�Ϊ���̬
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

void ds1032_DATAINPUT_init() //����˫��I/O�˿�Ϊ����̬
{
	GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	__HAL_RCC_GPIOB_CLK_ENABLE();
	GPIO_InitStruct.Pin = DS1302_DATA_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(DS1302_DATA_GPIO_Port, &GPIO_InitStruct);
}

void ds1302_write_onebyte(uint8_t data) //��DS1302����һ�ֽ�����
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
		} //��׼���������ٷ���
		SCLK_H; //����ʱ���ߣ���������
		data >>= 1;
	}
}

void ds1302_wirte_rig(uint8_t address, uint8_t data) //��ָ���Ĵ�����ַ��������
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

uint8_t ds1302_read_rig(uint8_t address) //��ָ����ַ��ȡһ�ֽ�����
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
	ds1032_DATAINPUT_init(); //����I/O��Ϊ����
	HAL_Delay(2);
	for (count = 0; count < 8; count++) {
		HAL_Delay(2); //ʹ��ƽ����һ��ʱ��
		return_data >>= 1;
		SCLK_H;
		HAL_Delay(4); //ʹ�ߵ�ƽ����һ��ʱ��
		SCLK_L;
		HAL_Delay(5); //��ʱ14us����ȥ��ȡ��ѹ������׼ȷ
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

    // ��������
    int day, month, year;
    parse_date(COMPILE_DATE, &day, &month, &year);

    // ����ʱ��
    int hour, min, sec;
    parse_time(COMPILE_TIME, &hour, &min, &sec);

    if(Time_now.year!=year||Time_now.minute!=min){
    	//����Time_now
    	Time_now.second = sec;
    	Time_now.minute = min;
    	Time_now.hour = hour;
    	Time_now.day = day;
    	Time_now.month = month;
    	Time_now.week = 7;
    	Time_now.year = year;
        // ת�����ݸ�ʽ
        uint8_t bcd_sec = int_to_bcd(sec);
        uint8_t bcd_min = int_to_bcd(min);
        uint8_t bcd_hour = int_to_bcd(hour);
        uint8_t bcd_day = int_to_bcd(day);
        uint8_t bcd_month = int_to_bcd(month);
        uint8_t bcd_year = int_to_bcd(year % 100); // ȡ��ݺ���λ

        // ��ʼ��DS1302
        ds1302_wirte_rig(0x8e, 0x00);  // �ر�д����

        ds1302_wirte_rig(0x80, bcd_sec);    // ��
        ds1302_wirte_rig(0x82, bcd_min);    // ��
        ds1302_wirte_rig(0x84, bcd_hour);   // ʱ��24Сʱ�ƣ�
        ds1302_wirte_rig(0x86, bcd_day);    // ��
        ds1302_wirte_rig(0x88, bcd_month);  // ��
        ds1302_wirte_rig(0x8a, 0x07);       // ���ڣ���������룬����ʹ���գ�
        ds1302_wirte_rig(0x8c, bcd_year);   // ��

        ds1302_wirte_rig(0x8e, 0x80);  // ����д����
    }

}

void ds1032_update(TIMEData time) {
	ds1302_wirte_rig(0x8e, 0x00); //�ر�д����
	ds1302_wirte_rig(0x80, int_to_bcd(time.second)); //seconds��
	ds1302_wirte_rig(0x82, int_to_bcd(time.minute)); //minutes��
	ds1302_wirte_rig(0x84, int_to_bcd(time.hour)); //hoursʱ
	ds1302_wirte_rig(0x86, int_to_bcd(time.day)); //date��
	ds1302_wirte_rig(0x88, int_to_bcd(time.month)); //months��
	ds1302_wirte_rig(0x8a, 0x07); //days
	ds1302_wirte_rig(0x8c, int_to_bcd(time.year%100)); //year��
	ds1302_wirte_rig(0x8e, 0x80); //�ر�д����
	HAL_Delay(10);
}

void ds1032_read_time() {
	read_time[0] = ds1302_read_rig(0x81); //����
	read_time[1] = ds1302_read_rig(0x83); //����
	read_time[2] = ds1302_read_rig(0x85); //��ʱ
	read_time[3] = ds1302_read_rig(0x87); //����
	read_time[4] = ds1302_read_rig(0x89); //����
	read_time[5] = ds1302_read_rig(0x8B); //������
	read_time[6] = ds1302_read_rig(0x8D); //����
}

void ds1032_read_realTime() {
	ds1032_read_time();  //BCD��ת��Ϊ10����
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
    // ��ȡʮλ�͸�λ
	uint8_t tens = num / 10;
	uint8_t units = num % 10;
    // ��ʮλ�͸�λת��Ϊ4λBCD�벢���
    uint8_t bcd = (tens << 4) | units;
    return bcd;
}

// �·��ַ���ת���ֵĸ�������
uint8_t month_str_to_num(const char* month) {
    const char* months[] = {"Jan","Feb","Mar","Apr","May","Jun",
                            "Jul","Aug","Sep","Oct","Nov","Dec"};
    for (int i = 0; i < 12; i++) {
        if (strncmp(month, months[i], 3) == 0) {
            return i + 1; // �·ݴ�1��ʼ
        }
    }
    return 1; // Ĭ��1��
}

// �������ַ�������ȡ�ա��¡���
void parse_date(const char* date_str, int* day, int* month, int* year) {
    char month_str[4];
    // ��ȡ�·�
    month_str[0] = date_str[0];
    month_str[1] = date_str[1];
    month_str[2] = date_str[2];
    month_str[3] = '\0';
    *month = month_str_to_num(month_str);

    // ��ȡ��
    *day = (date_str[4] - '0') * 10 + (date_str[5] - '0');

    // ��ȡ��
    *year = (date_str[7] - '0') * 1000 + (date_str[8] - '0') * 100 +
            (date_str[9] - '0') * 10 + (date_str[10] - '0');
}

// ��ʱ���ַ�������ȡʱ���֡���
void parse_time(const char* time_str, int* hour, int* min, int* sec) {
    *hour = (time_str[0] - '0') * 10 + (time_str[1] - '0');
    *min  = (time_str[3] - '0') * 10 + (time_str[4] - '0');
    *sec  = (time_str[6] - '0') * 10 + (time_str[7] - '0');
}
