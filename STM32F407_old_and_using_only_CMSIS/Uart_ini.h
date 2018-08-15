#include "stm32f407xx.h"
#include "stm32f4xx.h"
#include "string.h"


char uart4_rx_buf[128];
uint8_t uart4_rx_bit;
char uart_data;

void USART_ini(void){
	RCC->AHB1ENR |=RCC_AHB1ENR_GPIOCEN;
	GPIOC->MODER &=~GPIO_MODER_MODER10_0|GPIO_MODER_MODER11_0;
	GPIOC->MODER |=GPIO_MODER_MODER10_1|GPIO_MODER_MODER11_1;
	GPIOC->PUPDR |=GPIO_PUPDR_PUPDR10_0|GPIO_PUPDR_PUPDR11_0;
	GPIOC->PUPDR &=~GPIO_PUPDR_PUPDR10_1|GPIO_PUPDR_PUPDR11_1;
	GPIOC->OSPEEDR |=GPIO_OSPEEDER_OSPEEDR10_0|GPIO_OSPEEDER_OSPEEDR11_0|GPIO_OSPEEDER_OSPEEDR10_1|GPIO_OSPEEDER_OSPEEDR11_1;
	GPIOC->AFR[1]=0x8800;
	
	RCC->APB1ENR |=RCC_APB1ENR_UART4EN;
	UART4->BRR=0x683;//600bod
	UART4->CR1 |=USART_CR1_RE|USART_CR1_TE;//Enable Receiver and Transmitter and UART
	UART4->CR2 &=~USART_CR2_STOP_0;
	UART4->CR2 |=USART_CR2_STOP_1;
//	UART4->DR=10;
//UART4->DR=0x0;
UART4->CR1 |=USART_CR1_UE;
	
	UART4->DR=0x0D;
	NVIC_SetPriority(UART4_IRQn,0);
	NVIC_EnableIRQ(UART4_IRQn);
	UART4->CR1 |= USART_CR1_RXNEIE;
}


void UART_Send_Byte(uint8_t data)
	{
	while(!(UART4->SR & USART_SR_TC));
 UART4->DR=data;
}


void UART_Send_str (char *string){
	uint8_t i=0;
	while (string[i]){
		UART_Send_Byte(string[i]);
		i++;
	}
}


void UART4_IRQHandler(void)
{
	
	
	if (UART4->SR & USART_SR_RXNE)
	{
		UART4->DR = UART4->DR;
		uart_data=UART4->DR; //Считываем то что пришло в переменную...
   uart4_rx_buf[uart4_rx_bit]=UART4->DR; //Помещаем принятый байт в буфер.
   uart4_rx_bit++; //Наращиваем счётчик байтов буфера.
 
   if(uart_data=='\r') //Если пришло сообщение о нажатии Enter...
   {
	 GPIOD->BSRR |=(GPIO_BSRR_BR_15|GPIO_BSRR_BR_14|GPIO_BSRR_BR_13|GPIO_BSRR_BR_12);
   
   if(strcmp(uart4_rx_buf,"led15on\r")==0) //Если пришла команда "led0"
   {
	 GPIOD->BSRR |=GPIO_BSRR_BS_15;
   }
   else if(strcmp(uart4_rx_buf,"led14on\r")==0) //Если пришла команда "led1"
   {
   GPIOD->BSRR |=GPIO_BSRR_BS_14;
   }
   else if(strcmp(uart4_rx_buf,"led13on\r")==0) //Если пришла команда "led2"
   {
   GPIOD->BSRR |=GPIO_BSRR_BS_13;
   }
   else if(strcmp(uart4_rx_buf,"led12on\r")==0) //Если пришла команда "led3"
   {
   GPIOD->BSRR |=GPIO_BSRR_BS_12;
   }
   else
   {
   UART_Send_str("\n"); //Переходим на новую строку
   UART_Send_str("String: ");
   UART_Send_str(uart4_rx_buf); //Отправляем ее обратно в консоль
   }
 
   memset(uart4_rx_buf, 0, sizeof(uart4_rx_buf)); //Очищаем буфер
   uart4_rx_bit=0; //Сбрасываем счетчик
   UART_Send_str("\n");
   }
   }
		
		
	}

