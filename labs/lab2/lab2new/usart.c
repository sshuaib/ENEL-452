/*Salman Shuaib
	200374212
	ENEL 452
	Lab 2
*/

#include "stm32f10x.h"
#include "usart.h"
#include "cli.h"
#include <string.h>

void usartConfig(void) {
	// Enable AFIO and Port A 
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_AFIOEN;
	
	// Configuring PA2 for alternate function output push-pull, max speed 50 MHz
	GPIOA->CRL |= GPIO_CRL_CNF2_1 | GPIO_CRL_MODE2;
	GPIOA->CRL &= ~GPIO_CRL_CNF2_0;
	
	// Configuring PA3 as input pull-up/pull down
	GPIOA->CRL |= GPIO_CRL_CNF3_1;
	GPIOA->CRL &= ~GPIO_CRL_CNF3_0 & ~GPIO_CRL_MODE3;
}

void serial_open(void)
{
	RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
	USART2->CR1 |= USART_CR1_UE;
	USART2->BRR |= 0x138;  
	USART2->CR1 |= USART_CR1_TE | USART_CR1_RE;
	USART2->CR2 &= ~USART_CR2_STOP;
	USART2->CR1 |= USART_CR1_M;
}

void serial_close(void)
{
	RCC->APB1ENR &= ~RCC_APB1ENR_USART2EN;
	USART2->CR1 = 0;
	USART2->BRR =0; 
}

void print_message(char message[])
{
	CLI_Transmit((uint8_t*) message, strlen(message));
}

uint8_t getByte(void)
{
	uint8_t value;
	while(!(USART2->SR & USART_SR_RXNE))
	{
	}
	value = USART2->DR;
	return value;
}

int sendByte(uint8_t c)
{
	if(!(USART2->CR1 & USART_CR1_UE))
	{
		return 1;
	}
	
	while(!(USART2->SR & USART_SR_TXE))
	{
	}
	
	USART2->DR = c;
	return 0;
}

void delay(uint32_t delay)
{
	while (delay--){}
}


void ledinit(void)
{
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN; 
	
	GPIOA->CRL |= GPIO_CRL_MODE5;
	GPIOA->CRL &= ~GPIO_CRL_CNF5;
}

void led1ON(void)
{
	//GPIOA->ODR |= GPIO_ODR_ODR5;
	GPIOA->BSRR = NUC_GREEN_ON
}

void led1OFF(void)
{
	//GPIOA->ODR &= ~ GPIO_ODR_ODR5;
	GPIOA->BSRR = NUC_GREEN_OFF
}
