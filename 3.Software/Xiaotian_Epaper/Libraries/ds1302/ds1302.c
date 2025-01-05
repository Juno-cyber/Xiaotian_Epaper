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
	ds1302_wirte_rig(0x8e, 0x00); //关闭写保护
	ds1302_wirte_rig(0x80, 0x00); //seconds37秒
	ds1302_wirte_rig(0x82, 0x14); //minutes44分
	ds1302_wirte_rig(0x84, 0x09); //hours9时
	ds1302_wirte_rig(0x86, 0x05); //date30日
	ds1302_wirte_rig(0x88, 0x01); //months11月
	ds1302_wirte_rig(0x8a, 0x07); //days星期六
	ds1302_wirte_rig(0x8c, 0x25); //year2024年
	ds1302_wirte_rig(0x8e, 0x80); //关闭写保护
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

