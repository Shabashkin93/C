#include <stdio.h>
#include <stdlib.h>

void SysTick_Handler(void){//1ms
if (delay_count>0){
delay_count--;
}
}
void delay_ms(int delay_temp){
delay_count=delay_temp;
	while(delay_count){}
}
	
void GPIO_LCD_INI(void){//SETTING PIN FOR LCD 2004A
	RCC->AHB1ENR |=	RCC_AHB1ENR_GPIODEN;
	GPIOD->MODER |=((GPIO_MODER_MODER0_0)|(GPIO_MODER_MODER1_0)|(GPIO_MODER_MODER2_0)|(GPIO_MODER_MODER3_0)|(GPIO_MODER_MODER4_0)|(GPIO_MODER_MODER5_0)|(GPIO_MODER_MODER6_0)|(GPIO_MODER_MODER7_0)|(GPIO_MODER_MODER8_0)|(GPIO_MODER_MODER9_0)|(GPIO_MODER_MODER10_0));
	GPIOD->MODER &=~((GPIO_MODER_MODER0_1)|(GPIO_MODER_MODER1_1)|(GPIO_MODER_MODER2_1)|(GPIO_MODER_MODER3_1)|(GPIO_MODER_MODER4_1)|(GPIO_MODER_MODER5_1)|(GPIO_MODER_MODER6_1)|(GPIO_MODER_MODER7_1)|(GPIO_MODER_MODER8_1)|(GPIO_MODER_MODER9_1)|(GPIO_MODER_MODER10_1));
	GPIOD->OTYPER &=~((GPIO_OTYPER_OT_0)|(GPIO_OTYPER_OT_1)|(GPIO_OTYPER_OT_2)|(GPIO_OTYPER_OT_3)|(GPIO_OTYPER_OT_4)|(GPIO_OTYPER_OT_5)|(GPIO_OTYPER_OT_6)|(GPIO_OTYPER_OT_7)|(GPIO_OTYPER_OT_8)|(GPIO_OTYPER_OT_9)|(GPIO_OTYPER_OT_10));	
	GPIOD->OSPEEDR &=~((GPIO_OSPEEDER_OSPEEDR0_0)|(GPIO_OSPEEDER_OSPEEDR1_0)|(GPIO_OSPEEDER_OSPEEDR2_0)|(GPIO_OSPEEDER_OSPEEDR3_0)|(GPIO_OSPEEDER_OSPEEDR4_0)|(GPIO_OSPEEDER_OSPEEDR5_0)|(GPIO_OSPEEDER_OSPEEDR6_0)|(GPIO_OSPEEDER_OSPEEDR7_0)|(GPIO_OSPEEDER_OSPEEDR8_0)|(GPIO_OSPEEDER_OSPEEDR9_0)|(GPIO_OSPEEDER_OSPEEDR10_0));	
	GPIOD->OSPEEDR |=((GPIO_OSPEEDER_OSPEEDR0_1)|(GPIO_OSPEEDER_OSPEEDR1_1)|(GPIO_OSPEEDER_OSPEEDR2_1)|(GPIO_OSPEEDER_OSPEEDR3_1)|(GPIO_OSPEEDER_OSPEEDR4_1)|(GPIO_OSPEEDER_OSPEEDR5_1)|(GPIO_OSPEEDER_OSPEEDR6_1)|(GPIO_OSPEEDER_OSPEEDR7_1)|(GPIO_OSPEEDER_OSPEEDR8_1)|(GPIO_OSPEEDER_OSPEEDR9_1)|(GPIO_OSPEEDER_OSPEEDR10_1));	
	}
//Функция устанавливает 0 на всех пинах.
void Clear_ports(void){
	D4_OFF;
	D5_OFF;
	D6_OFF;
	D7_OFF;
}
//Указываем необходимые порты как выходы
void Init_ports(void){
	GPIO_LCD_INI();
	Clear_ports(); 
}
//отправка байта в дисплей,если IsData=1 то будет выведен символ,если 0 то команда дисплею
void SendByte(int ByteToSend, int IsData){
delay_ms(3);
	if (IsData == 1)
        LCM_OUT |= (RS);
    else
        LCM_OUT &= ~(RS);
	E_ON;
	delay_ms(1);
	LCM_OUT |= (ByteToSend& 0xF0);
	delay_ms(2);
	E_OFF;
	delay_ms(1);
	Clear_ports();
	//delay_ms(2);
	E_ON;
	if (IsData == 1)
        LCM_OUT |= (RS);
    else
        LCM_OUT &= ~(RS);
	delay_ms(1);
	LCM_OUT |= ((ByteToSend & 0x0F) << 4);
	delay_ms(2);
	E_OFF;
	delay_ms(1);
	Clear_ports();
	delay_ms(3);
}
//возвращает длину слова
int strLength(const char* str){
    int size = 0;
    while(*str++) ++size;
    return size;
}
//возвращает код буквы в цифрах в ответ на букву
int cod (char b){
int f=1;//итоговое число,пусть пока будет равно 1
int j=0;//порядковый номер элемента массива
while (j<90){	//сравнение введённого символа с массивом допустимых символов
	if (b==simb[j]){
		f=cod_simb[j];	
	}
		j++;	 
}
return f;//выдача обозначения введённого символа
}
//выводит символы на экран
void Print_Lcd(const char* hh){
int lenght=0;
int i=0;
	int y=0;
lenght=strLength(hh);
while(i<lenght){	
y= cod(hh[i]);
i++;
SendByte(y,1);
}

}
//Очистка дисплея и ввод сначала
void Clr_display(void){//Очистка дисплея и ввод сначала
	SendByte(0x1,0);
}
//возврат домой,тоесть курсор вначало
void Return_Home(void){
	SendByte(0x2,0);
}
//включить дисплей,курсор выключен,курсор не мигает
void Display_On(void){
	SendByte(0xC,0);
}
//сдвиг курсора влево
void Shift_Curs_Left(void){
	SendByte(0x10,0);
}
//сдвиг курсора вправо
void Shift_Curs_Right(void){
	SendByte(0x14,0);
}
//сдвиг дисплея влево
void Shift_Display_Left(void){
	SendByte(0x18,0);
}
//сдвиг дисплея вправо
void Shift_Display_Right(void){
	SendByte(0x1C,0);
}
//8бит,2 строки,шрифт маленький тк не даёт большой на 2х строках
void Function_Set(void){
	SendByte(0x38,0);
}
//курсор сдвигается каждый раз на один символ вперёд
void Enty_Mode_Set(void){
	SendByte(0x6,0);
}
// функция инициализации модуля ЖКИ.4 бит,2 строки,символы 5*8
void Init_LCD(void){
	delay_ms(30);
	Clear_ports();
	//Function_Set
	E_ON;
	delay_ms(1);
D5_ON;
delay_ms(2);
	E_OFF;
	delay_ms(1);
	Clear_ports();
	delay_ms(3);
E_ON;
	delay_ms(1);
	D5_ON;
	delay_ms(2);
	E_OFF;
	delay_ms(1);
	Clear_ports();
	delay_ms(2);
	E_ON;
delay_ms(1);
D7_ON;
delay_ms(2);
	E_OFF;
	delay_ms(1);
	Clear_ports();
	delay_ms(3);
	E_ON;
	delay_ms(3);
	E_OFF;
	delay_ms(1);
	Clear_ports();
	delay_ms(2);
	E_ON;
	delay_ms(1);
	D7_ON;D6_ON;D5_ON;
	delay_ms(2);
	E_OFF;
	delay_ms(1);
	Clear_ports();
	
	delay_ms(3);
	E_ON;
	delay_ms(3);
	E_OFF;
	delay_ms(1);
	Clear_ports();
	delay_ms(2);
	E_ON;
	delay_ms(1);
	D6_ON;D5_ON;
	delay_ms(2);
	E_OFF;
	delay_ms(1);
	Clear_ports();
	
	delay_ms(3);
	E_ON;
	delay_ms(1);
	delay_ms(2);
	E_OFF;
	delay_ms(1);
	Clear_ports();
	delay_ms(2);
	E_ON;
	delay_ms(1);
	D4_ON;
	delay_ms(2);
	E_OFF;
	delay_ms(1);
	Clear_ports();
}
//установка курсора (номер строки,номер в строке)
void curs(int str,int num){
	int c=0x0;
	int s=0x0;
	switch (str){
case 1:
		s=0x80;
break;
case 3:
	s=0x93;
break;
case 2:
	s=0xC0;
break;
case 4:
	s=0xD3;
break;
default:
	s=0x80;
	}	
	c=s+num;
	SendByte(c,0);
}

void Print_SQRT(void){//знак квадратного корня
	SendByte(0xE8,1);
}

int getCountsOfDigits(int n) {//возвращает количество цифр в числе
        if (n < 100000) {
            if (n < 100) {
                if (n < 10) {
                    return 1;
                } else {
                    return 2;
                }
            } else {
                if (n < 1000) {
                    return 3;
                } else {
                    if (n < 10000) {
                        return 4;
                    } else {
                        return 5;
                    }
                }
            }
        } else {
            if (n < 10000000) {
                if (n < 1000000) {
                    return 6;
                } else {
                    return 7;
                }
            } else {
                if (n < 100000000) {
                    return 8;
                } else {
                    if (n < 1000000000) {
                        return 9;
                    } else {
                        return 10;
                    }
                }
            }
        }
    }