#ifndef LCD_H_
#define LCD_H_
//------------------------------------------------
#include "stm32f1xx_hal.h"
//------------------------------------------------
#define e_set() LCD_WriteByteI2CLCD(CommParam, portlcd|=0x04)  //установка линии Е в 1
#define e_reset() LCD_WriteByteI2CLCD(CommParam, portlcd&=~0x04) //установка линии Е в 0
#define rs_set() LCD_WriteByteI2CLCD(CommParam, portlcd|=0x01) //установка линии RS в 1
#define rs_reset() LCD_WriteByteI2CLCD(CommParam, portlcd&=~0x01) //установка линии RS в 0
#define setled() LCD_WriteByteI2CLCD(CommParam, portlcd|=0x08) //установка линии RS в 1
#define setwrite() LCD_WriteByteI2CLCD(CommParam, portlcd&=~0x02) //установка линии RS в 0
//------------------------------------------------

//Нужно на случай если дисплей не один, а несколько на разных адресах и портах
struct communicationParameters{
	I2C_HandleTypeDef* i2cPortMaster;
	uint8_t adressSlave;
};

//отправка байта в дисплей,если IsData=1 то будет выведен символ,если 0 то команда дисплею
void SendByte(struct communicationParameters CommParam, uint8_t ByteToSend, uint8_t IsData);

void LCD_WriteByteI2CLCD(struct communicationParameters CommParam, uint8_t bt);

//выводит строку на экран
void LCD_String(struct communicationParameters CommParam, char* st);
//Выводит символ на экран
void LCD_SendChar(struct communicationParameters CommParam, char ch);
//Очистка дисплея и ввод сначала
void LCD_Clear(struct communicationParameters CommParam);

//возврат домой, т.е. курсор вначало
void LCD_ReturnHome(struct communicationParameters CommParam);

//включить дисплей,курсор выключен,курсор не мигает
void LCD_On(struct communicationParameters CommParam);

//сдвиг курсора влево
void LCD_ShiftCursorToLeft(struct communicationParameters CommParam);

//сдвиг курсора вправо
void LCD_ShiftCursorToRight(struct communicationParameters CommParam);

//сдвиг дисплея влево
void LCD_ShiftLCDToLeft(struct communicationParameters CommParam);

//сдвиг дисплея вправо
void LCD_ShiftLCDToRight(struct communicationParameters CommParam);

//8бит,2 строки,шрифт маленький тк не даёт большой на 2х строках
void LCD_FunctionSet(struct communicationParameters CommParam);

//курсор сдвигается каждый раз на один символ вперёд
void LCD_EntyModeSet(struct communicationParameters CommParam);

// функция инициализации модуля ЖКИ.4 бит,2 строки,символы 5*8
void LCD_ini(struct communicationParameters CommParam);
	
//установка курсора (номер строки,номер в строке)
void LCD_SetCursor(struct communicationParameters CommParam, int str, int num);

void LCD_PrintSQRT(struct communicationParameters CommParam);//знак квадратного корня

void LCD_PrintSVASTIKA (struct communicationParameters CommParam);

//------------------------------------------------
#endif /* LCD_H_ */