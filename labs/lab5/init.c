/*Salman Shuaib
	200374212
	ENEL 452
	Lab 5
*/
#include "init.h"
#include "cli.h"
#include <string.h>

void led_init(void)
{
	// Enable clock for Port A
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN; 
	// Configure PA5 as a push pull output with 50Mhz speed
	GPIOA->CRL |= GPIO_CRL_MODE5;
  GPIOA->CRL &= ~GPIO_CRL_CNF5;
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
