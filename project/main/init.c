/*Salman Shuaib
	200374212
	ENEL 452
	Lab 5
*/

#include "init.h"
#include "cli.h"
#include "FreeRTOS.h"
#include <string.h>

void led_init(void)
{
	// Enable clock for Port A
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	
	// Configure PA5 as a push pull output with 50Mhz speed
	GPIOA->CRL |= GPIO_CRL_MODE5;
  GPIOA->CRL &= ~GPIO_CRL_CNF5;
	
	GPIOA->CRH |= GPIO_CRH_MODE9_0 | GPIO_CRH_MODE9_1;
	GPIOA->CRH &= ~GPIO_CRH_CNF9_0 & ~GPIO_CRH_CNF9_1;
}

void initInterrupt(void)
{
RCC->APB2ENR |= RCC_APB2ENR_IOPCEN | RCC_APB2ENR_AFIOEN;
//AFIO->EXTICR[3] &= ~AFIO_EXTICR4_EXTI13;
AFIO->EXTICR[3] |= AFIO_EXTICR4_EXTI13_PC;
EXTI->IMR |= EXTI_IMR_MR13; // Unmask PC13 as interrupt source
EXTI->FTSR |= EXTI_FTSR_TR13;
NVIC->ISER[1] = NVIC_ISER_SETENA_8;
}


void redled_on(void)
{
		GPIOA->ODR |= GPIO_ODR_ODR9;
}

void redled_off(void)
{
		GPIOA->ODR &= ~GPIO_ODR_ODR9;
}

void led_on(void)
{
	GPIOA->ODR |= GPIO_ODR_ODR5;
}

void led_off(void)
{
	GPIOA->ODR &= ~GPIO_ODR_ODR5;
}

void print_message(char message[])
{
	CLI_Transmit((uint8_t*) message, strlen(message), 100);
}
