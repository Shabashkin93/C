#include "gpio_ini.h"
#include "stm32f4xx.h"                  // Device header
#include "stm32f407xx.h"
#include "my_define.h"
void LEDs_ini(void){
RCC->AHB1ENR|=RCC_AHB1ENR_GPIODEN;//тактирование порта D,тактируем весь порт
		//установка на выход 12,13,14,15 выводов порта D 10 10 10 10 00000000000000000000000
//00: Input (reset state)
//01: General purpose output mode
//10: Alternate function mode
//11: Analog mode
		//GPIOD->MODER |=GPIO_MODER_MODER15_0;MODER15-вывод 15;0-нулевой бит
		
		GPIOD->MODER &=~GPIO_MODER_MODER15_1;
			GPIOD->MODER |=GPIO_MODER_MODER15_0;
GPIOD->MODER &=~GPIO_MODER_MODER1_1;
			GPIOD->MODER |=GPIO_MODER_MODER1_0;
	GPIOD->MODER &=~GPIO_MODER_MODER2_1;
			GPIOD->MODER |=GPIO_MODER_MODER2_0;
	GPIOD->MODER &=~GPIO_MODER_MODER3_1;
			GPIOD->MODER |=GPIO_MODER_MODER3_0;
	GPIOD->MODER &=~GPIO_MODER_MODER4_1;
			GPIOD->MODER |=GPIO_MODER_MODER4_0;
		//подтягивающий резистр включен на всём порте D
    //0: Output push-pull (reset state)-подтягивающий резистор
		//1:Output open-drain-открытый колектор
		GPIOD->OTYPER &=~GPIO_OTYPER_OT_15;
		GPIOD->OTYPER &=~GPIO_OTYPER_OT_1;
		GPIOD->OTYPER &=~GPIO_OTYPER_OT_2;
		GPIOD->OTYPER &=~GPIO_OTYPER_OT_3;
		GPIOD->OTYPER &=~GPIO_OTYPER_OT_4;
		//установка скорости 
//00: Low speed
//01: Medium speed
//10: High speed
//11: Very high speed
		GPIOD->OSPEEDR &=~GPIO_OSPEEDER_OSPEEDR15;
		GPIOD->OSPEEDR &=~GPIO_OSPEEDER_OSPEEDR1;
		GPIOD->OSPEEDR &=~GPIO_OSPEEDER_OSPEEDR2;
		GPIOD->OSPEEDR &=~GPIO_OSPEEDER_OSPEEDR3;
		GPIOD->OSPEEDR &=~GPIO_OSPEEDER_OSPEEDR4;

		//установка лог уровня(напряжения) 1-высокое,0- низкое
	}

//GPIO_InitTypeDef GPIO_Init_LED;

//RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);

//GPIO_Init_LED.GPIO_Pin = GPIO_Pin12|GPIO_Pin13|GPIO_Pin14|GPIO_Pin15;
//GPIO_Init_LED.GPIO_Mode=GPIO_Mode_OUT;
//GPIO_Init_LED.GPIO_Speed=GPIO_Speed_2MHz;
//GPIO_Init_LED.GPIO_OType=GPIO_OType_PP;
//GPIO_Init_LED.GPIO_PuPd=GPIO_PuPd_NOPULL;

//GPIO_Init(GPIOD, &GPIO_Init_LED);

//}
	void Button_ini(void){
		//тактирование порта C
		RCC->AHB1ENR|=RCC_AHB1ENR_GPIOAEN;
		//настройка вывода 0 на вход
		GPIOA->MODER &=~ GPIO_MODER_MODER0_0;
		GPIOA->MODER &=~GPIO_MODER_MODER0_1;
	}	