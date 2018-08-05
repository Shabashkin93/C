#include <stdio.h>
#include <stdlib.h>
#include "lcd2004a.h"


extern I2C_HandleTypeDef hi2c1;



//Select controller port and display address
uint8_t buf[1]={0};

char str1[100];
uint8_t portlcd; //ячейка для хранения данных порта микросхемы расширения

void LCD_WriteByteI2CLCD(struct communicationParameters CommParam, uint8_t bt)
{
	buf[0]=bt;
	HAL_I2C_Master_Transmit(CommParam.i2cPortMaster,(uint16_t) (CommParam.adressSlave)<<1, buf, 1, 1000);
}

void SendHalfByte(struct communicationParameters CommParam, uint8_t c)
{
	c<<=4;
	e_set();//включаем линию E
	LCD_WriteByteI2CLCD(CommParam, portlcd|c);
	e_reset();//выключаем линию E
}

//отправка байта в дисплей,если IsData=1 то будет выведен символ,если 0 то команда дисплею

void SendByte(struct communicationParameters CommParam, uint8_t ByteToSend, uint8_t IsData)
{
	if(IsData==0) rs_reset();
	else rs_set();
	uint8_t hc=0;
	hc=ByteToSend>>4;
	SendHalfByte(CommParam, hc);SendHalfByte(CommParam, ByteToSend);
}

//выводит символы на экран

void LCD_String(struct communicationParameters CommParam, char* st)
{
	uint8_t i=0;
	while(st[i]!=0)
	{
		SendByte(CommParam, st[i], 1);
		i++;
	}
}

void LCD_SendChar(struct communicationParameters CommParam, char ch)
{
	SendByte(CommParam, ch, 1);
}

//Очистка дисплея и ввод сначала
void LCD_Clear(struct communicationParameters CommParam){//Очистка дисплея и ввод сначала
	SendByte(CommParam, 0x1,0);
}
//возврат домой,тоесть курсор вначало
void LCD_ReturnHome(struct communicationParameters CommParam){
	SendByte(CommParam, 0x2,0);
}
//включить дисплей,курсор выключен,курсор не мигает
void LCD_On(struct communicationParameters CommParam){
	SendByte(CommParam, 0xC,0);
}
//сдвиг курсора влево
void LCD_ShiftCursorToLeft(struct communicationParameters CommParam){
	SendByte(CommParam, 0x10,0);
}
//сдвиг курсора вправо
void LCD_ShiftCursorToRight(struct communicationParameters CommParam){
	SendByte(CommParam, 0x14,0);
}
//сдвиг дисплея влево
void LCD_ShiftLCDToLeft(struct communicationParameters CommParam){
	SendByte(CommParam, 0x18, 0);
}
//сдвиг дисплея вправо
void LCD_ShiftLCDToRight(struct communicationParameters CommParam){
	SendByte(CommParam, 0x1C, 0);
}
//8бит,2 строки,шрифт маленький тк не даёт большой на 2х строках
void LCD_FunctionSet(struct communicationParameters CommParam){
	SendByte(CommParam, 0x38, 0);
}
//курсор сдвигается каждый раз на один символ вперёд
void LCD_EntyModeSet(struct communicationParameters CommParam){
	SendByte(CommParam, 0x6, 0);
}
// функция инициализации модуля ЖКИ.4 бит,2 строки,символы 5*8
void LCD_ini(struct communicationParameters CommParam)
{
	HAL_Delay(15);
	SendHalfByte(CommParam, 0x03);
	HAL_Delay(4);
	SendHalfByte(CommParam, 0x03);
	HAL_Delay(1);
	SendHalfByte(CommParam, 0x03);
	HAL_Delay(1);
	SendHalfByte(CommParam, 0x02);
	HAL_Delay(1);
	SendByte(CommParam, 0x28, 0);//режим 4 бит, 2 линии (для нашего большого дисплея это 4 линии, шрифт 5х8	
	HAL_Delay(1);
	SendByte(CommParam, 0x0C, 0);//дисплей включаем (D=1), курсоры никакие не нужны
	HAL_Delay(1);
	SendByte(CommParam, 0x01, 0);//уберем мусор
	HAL_Delay(2);
	SendByte(CommParam, 0x06, 0);//пишем влево
	HAL_Delay(1);
	setled();//подсветка
	setwrite();//запись
}

//установка курсора (номер строки,номер в строке)
void LCD_SetCursor(struct communicationParameters CommParam, int str, int num){
	int c=0x0;
	int s=0x0;
	switch (str){
case 0:
		s=0x80;
break;
case 2:
	s=0x93;
break;
case 1:
	s=0xC0;
break;
case 3:
	s=0xD3;
break;
default:
	s=0x80;
	}	
	c=s+num;
	SendByte(CommParam, c, 0);
}

void LCD_PrintSQRT(struct communicationParameters CommParam){//знак квадратного корня
	SendByte(CommParam, 0xE8, 1);
}
void LCD_PrintSVASTIKA (struct communicationParameters CommParam){
	SendByte(CommParam, 0x0, 0);
	
	SendByte(CommParam, 0x40, 0);
	SendByte(CommParam, 0x0, 1);
	
	SendByte(CommParam, 0x41, 0);
	SendByte(CommParam, 0x17, 1);
	
	SendByte(CommParam, 0x42, 0);
	SendByte(CommParam, 0x14, 1);
	
	SendByte(CommParam, 0x43, 0);
	SendByte(CommParam, 0x1F, 1);
	
	SendByte(CommParam, 0x44, 0);
	SendByte(CommParam, 0x5, 1);
	
	SendByte(CommParam, 0x45, 0);
	SendByte(CommParam, 0x1D, 1);
	
	SendByte(CommParam, 0x46, 0);
	SendByte(CommParam, 0x0, 1);
	
	SendByte(CommParam, 0x47, 0);
	SendByte(CommParam, 0x0, 1);
}