#include <stdio.h>
#include <stdlib.h>

#define     LCM_OUT               GPIOD->ODR
#define     LCM_PIN_MASK  ((GPIO_ODR_ODR_8 | GPIO_ODR_ODR_10 | GPIO_ODR_ODR_7 | GPIO_ODR_ODR_6 | GPIO_ODR_ODR_5 | GPIO_ODR_ODR_4))
#define RS GPIO_ODR_ODR_8
#define E GPIO_ODR_ODR_10
#define D7_ON GPIOD->BSRR=GPIO_BSRR_BS_7;
#define D7_OFF GPIOD->BSRR=GPIO_BSRR_BR_7;
#define D6_ON GPIOD->BSRR=GPIO_BSRR_BS_6;
#define D6_OFF GPIOD->BSRR=GPIO_BSRR_BR_6;
#define D5_ON GPIOD->BSRR=GPIO_BSRR_BS_5;
#define D5_OFF GPIOD->BSRR=GPIO_BSRR_BR_5;
#define D4_ON GPIOD->BSRR=GPIO_BSRR_BS_4;
#define D4_OFF GPIOD->BSRR=GPIO_BSRR_BR_4;
#define RS_ON GPIOD->BSRR=GPIO_BSRR_BS_8;
#define RS_OFF GPIOD->BSRR=GPIO_BSRR_BR_8;
#define E_ON GPIOD->BSRR=GPIO_BSRR_BS_10;
#define E_OFF GPIOD->BSRR=GPIO_BSRR_BR_10;
#define DINAMSTR [] = ""
char simb[90]=" ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!#$%&()*+-./@:;<=>?[]^_`{|}";
int cod_simb[90]={0x80,0x41,0x42,0x43,0x44,0x45,0x46,0x47,0x48,0x49,0x4A,0x4B,0x4C,0x4D,0x4E,0x4F
	,0x50,0x51,0x52,0x53,0x54,0x55,0x56,0x57,0x58,0x59,0x5A,
0x61,0x62,0x63,0x64,0x65,0x66,0x67,0x68,0x69,0x6A,0x6B,0x6C,0x6D,0x6E,0x6F,
	0x70,0x71,0x72,0x73,0x74,0x75,0x76,0x77,0x78,0x79,0x7A,
0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,
	0x21,0x23,0x24,0x25,0x26,0x28,0x29,0x2A,0x2B,
0x2C,0x2D,0x2F,0x40,0x3A,0x3B,0x3C,0x3D,0x3E,0x3F,0x5B,0x5D,0x5E,0x5F,0x60,0x7B,0x7C,0x7D
};

uint16_t delay_count=0;

void SysTick_Handler(void);
}
void delay_ms(int delay_temp);
	
void GPIO_LCD_INI(void);
//Функция устанавливает 0 на всех пинах.
void Clear_ports(void);
//Указываем необходимые порты как выходы
void Init_ports(void);
//отправка байта в дисплей,если IsData=1 то будет выведен символ,если 0 то команда дисплею
void SendByte(int ByteToSend, int IsData);
//возвращает длину слова
int strLength(const char* str);
//возвращает код буквы в цифрах в ответ на букву
int cod (char b);
//выводит символы на экран
void Print_Lcd(const char* hh);
//Очистка дисплея и ввод сначала
void Clr_display(void);
//возврат домой,тоесть курсор вначало
void Return_Home(void);
//включить дисплей,курсор выключен,курсор не мигает
void Display_On(void);
//сдвиг курсора влево
void Shift_Curs_Left(void);
//сдвиг курсора вправо
void Shift_Curs_Right(void);
//сдвиг дисплея влево
void Shift_Display_Left(void);
//сдвиг дисплея вправо
void Shift_Display_Right(void);
//8бит,2 строки,шрифт маленький тк не даёт большой на 2х строках
void Function_Set(void);
//курсор сдвигается каждый раз на один символ вперёд
void Enty_Mode_Set(void);
// функция инициализации модуля ЖКИ.4 бит,2 строки,символы 5*8
void Init_LCD(void);
//установка курсора (номер строки,номер в строке)
void curs(int str,int num);
void Print_SQRT(void);//знак квадратного корня

int getCountsOfDigits(int n); //возвращает количество цифр в числе