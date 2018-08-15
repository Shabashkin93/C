#include "stm32f4xx.h"
#include "stm32f407xx.h"
#define SERVO_180 8200
#define SERVO_0 4800

void set_pos(uint8_t pos) {
uint32_t tmp=(SERVO_180 - SERVO_0) /180 ;
TIM4->CCR4 = SERVO_0 + tmp * pos;
}

void Servo(void){
	
	
//	//тактирование порта C
//		RCC->AHB1ENR|=RCC_AHB1ENR_GPIOAEN;
//		//настройка вывода 0 на вход
//		GPIOA->MODER &=~ GPIO_MODER_MODER0_0;
//		GPIOA->MODER &=~GPIO_MODER_MODER0_1;
//	
	RCC->APB1ENR |= RCC_APB1ENR_TIM4EN; //Подаем тактовые импульсы на таймер 4
	RCC->CFGR |=RCC_CFGR_PPRE1_0|RCC_CFGR_PPRE1_2;
	RCC->CFGR &=~RCC_CFGR_PPRE1_1;
	
//тактируем и настраиваем порт
RCC->AHB1ENR |=	RCC_AHB1ENR_GPIODEN;
GPIOD->MODER &=~GPIO_MODER_MODER15_0;
GPIOD->MODER |=GPIO_MODER_MODER15_1;
GPIOD->OSPEEDR |=GPIO_OSPEEDER_OSPEEDR15;
GPIOD->OTYPER &=~GPIO_OTYPER_OT_15;
GPIOD->PUPDR &=~GPIO_PUPDR_PUPDR15;
GPIOD->AFR[1] = 0x20000000;//PA1 - AFIO1 (TIM2_CH2)
////
		TIM4->CCER |=TIM_CCER_CC4E;//выбираем 4ый вывод из 4х возможных

		RCC->APB1ENR |= RCC_APB1ENR_TIM4EN; //Подаем тактовые импульсы на таймер 4
		TIM4->PSC=24;//Коэффициент деления 24000 получаем раз в милисекунду
		TIM4->ARR=1200;//Перезагружаемое значение 
		TIM4->CCMR2 |=TIM_CCR4_CCR4;//	set mode PWM
		TIM4->CCER |=TIM_CCER_CC4E;
		TIM4->CCMR2 |=TIM_CCMR2_OC4M_0|TIM_CCMR2_OC4M_1|TIM_CCMR2_OC4M_2;
		TIM4->CCR4=200;//set start value PWM
//		TIM4->DIER |=TIM_DIER_UIE;//Update interrupt enable
//		TIM4->CR1 |=TIM_CR1_CEN;//Counter enable
//		
////		if (GPIOA->IDR & GPIO_IDR_IDR_0){
		TIM4->CR1 |=TIM_CR1_CEN;
////		TIM4->EGR |=TIM_EGR_UG;
////		}
////		else{
////		TIM4->CR1 &=~TIM_CR1_CEN;
////		TIM4->EGR &=~TIM_EGR_UG;
////		}
//		
		TIM4->EGR |=TIM_EGR_UG;//Update Generation	
}
