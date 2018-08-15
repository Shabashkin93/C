#include "stm32f4xx.h"
#include "my_define.h"
#include "lcd2004a.h"
#include "stm32f407xx.h"
#include "keyboard16.h"
#include "PWM.h"
#include "Timer_6.h"
#include "Timer_2.h"
#include "Uart_ini.h"
#include "string.h"
#include "Encoder_ini.h"
#include "Servo_privod.h"

uint16_t dac=0;
char CNT1=0;
char CNT2=0;



uint8_t il = 0; //Переменная отображает текущее состояние светодиода - ON/OFF
void DAC_ini(void){
	RCC->AHB1ENR |=RCC_AHB1ENR_GPIOAEN;//ТАКТИРУЕМ ПОРТ А
	RCC->APB1ENR |=RCC_APB1ENR_DACEN;//ТАКТИРОВАНИЕ ЦАП
	GPIOA->MODER &=~GPIO_MODER_MODER4_0;
	GPIOA->MODER |=GPIO_MODER_MODER4_1;
	DAC->CR |=DAC_CR_TEN1;//ВКЛЮЧИТЬ ВНЕШНИЙ ЗАПУСК ПРЕОБРАЗОВАНИЯ
	DAC->CR |=DAC_CR_TSEL1;//ПРЕРЫВАНИЕ ОТ ТАЙМЕРА 6
	DAC->CR |=DAC_CR_WAVE1;//СИГНАЛ ТРЕУГОЛЬНОЙ ФОРМЫ
	DAC->CR |=DAC_CR_MAMP1;//АМПЛИТУДА МАКСИМАЛЬНАЯ ДО 4095
	DAC->CR |=DAC_CR_EN1;
//	DAC->DHR8R1=0xFF;
DAC->DHR8R1=dac;
}

void delay(void);

void delay(void) {
volatile uint32_t i;
for (i=1; i != 0x2FFFF; i++);
}
uint16_t i;
uint32_t pwm_arr[]={0,0,6553,13107,19660,26214,32768,
39321,45875,52428,58982,65535};


int io=0;
int ih=1;
int dela=0;
int main(){
SysTick_Config(SystemCoreClock/1000);//1us
	
	USART_ini();
	
	RCC->AHB1ENR|=RCC_AHB1ENR_GPIODEN;
	GPIOD->MODER |= ((GPIO_MODER_MODER15_0)|(GPIO_MODER_MODER14_0)|(GPIO_MODER_MODER13_0)|(GPIO_MODER_MODER12_0)); //Порт B в режиме "выход"
  GPIOD->OTYPER &= ~((GPIO_OTYPER_OT_15)|(GPIO_OTYPER_OT_14)|(GPIO_OTYPER_OT_13)|(GPIO_OTYPER_OT_12)); //Выход в режиме "push-pull"
  GPIOD->PUPDR &= ~((GPIO_PUPDR_PUPDR15)|(GPIO_PUPDR_PUPDR14)|(GPIO_PUPDR_PUPDR13)|(GPIO_PUPDR_PUPDR12)); //Подтягивающие резисторы не используются
  GPIOD->OSPEEDR |= ((GPIO_OSPEEDER_OSPEEDR15)|(GPIO_OSPEEDER_OSPEEDR14)|(GPIO_OSPEEDER_OSPEEDR13)|(GPIO_OSPEEDER_OSPEEDR12)); //Скорость работы порта максимальная
	
	
//RCC->AHB1ENR |=RCC_AHB1ENR_GPIOCEN;
//GPIOC->MODER |=GPIO_MODER_MODER10_1|GPIO_MODER_MODER11_1;
//GPIOC->MODER &=~GPIO_MODER_MODER10_0|GPIO_MODER_MODER11_0;

//GPIOC->AFR[1]=0x00008800;

//	RCC->APB1ENR |=RCC_APB1ENR_UART4EN;
//	UART4->CR1 |=USART_CR1_UE;
//	UART4->CR1 &=~USART_CR1_M;//1 start 8 data n stop
//	UART4->CR1 |=USART_CR1_PCE;
//	
//	
//	
//	
//	
//PWM_4_ini();
	
	

	UART_Send_str("UART ENABLE ");
	
	Encoder_ini();
	
	Servo();
	
	
while(1){
	
	CNT1=TIM5->CNT;
	if (CNT1!=CNT2){
		UART_Send_str(&CNT1);
		CNT2=CNT1;
	}
//	
//for (io=0;io<=180;io++) {
//delay();
//set_pos(io);
//}

	
//	while(ih<65535){
//	TIM4->CCR4=ih;
//		ih++;
//		if(ih==65535){
//			ih=0;
//		}
//	}
//	
//while(i<0xFFFF){
//	i++;
//			TIM4->CCR4=i;
//			for(;dela<100;dela++)__NOP();

}

}
