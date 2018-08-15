//инициализация таймера №2
//таймер 32х битный
//default frequence 24*10^6 24 мегагерц

#include "stm32f407xx.h"
#include "stm32f4xx.h"

uint8_t ij = 0; //Переменная отображает текущее состояние светодиода - ON/OFF

void TIM6_GPIO_ini (void){
	RCC->AHB1ENR |=	RCC_AHB1ENR_GPIODEN;
	//GPIOD init
  GPIOD->MODER |= ((GPIO_MODER_MODER15_0)|(GPIO_MODER_MODER14_0)); //Порт B в режиме "выход"
  GPIOD->OTYPER &= ~((GPIO_OTYPER_OT_15)|(GPIO_OTYPER_OT_14)); //Выход в режиме "push-pull"
  GPIOD->PUPDR &= ~((GPIO_PUPDR_PUPDR15)|(GPIO_PUPDR_PUPDR14)); //Подтягивающие резисторы не используются
  GPIOD->OSPEEDR |= ((GPIO_OSPEEDER_OSPEEDR15)|(GPIO_OSPEEDER_OSPEEDR14)); //Скорость работы порта максимальная
}

void Tim_6_ini(void){
	NVIC_SetPriority(TIM6_DAC_IRQn, 1); //Приоритет прерывания
  NVIC_EnableIRQ(TIM6_DAC_IRQn); //Разрешаем обработку прерывания от таймера 6
	RCC->APB1ENR |= RCC_APB1ENR_TIM6EN; //Подаем тактовые импульсы на таймер 6
	//prescaller
	TIM6->PSC=24000-1;//Коэффициент деления 24000 получаем раз в милисекунду
	//auto reload устанавливаем предел до которого тикает таймер
	TIM6->ARR=500;//Перезагружаемое значение 
	TIM6->DIER |=TIM_DIER_UIE;//Разрешаем прерывание при переполнении счетчика
	TIM6->CR1 |=TIM_CR1_CEN;//начать отсчёт
	
}
void TIM6_DAC_IRQHandler(void) //Функция обработчика прерывания от таймера 6
  {
    TIM6->SR &= ~TIM_SR_UIF; //Сбрасываем бит вызова прерывания. 
    if (ij == 0) //Проверяем текущее состояние светодиода - ON/OFF
      GPIOD->BSRR |= GPIO_BSRR_BS_15; //Зажигаем светодиод
    else
     GPIOD->BSRR |= GPIO_BSRR_BR_15; //Или гасим светодиод
    ij = ~ij; //Изменяем переменную, отображающую текушее состояние светодиода
  }
