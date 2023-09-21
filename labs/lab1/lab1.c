#include "stm32f10x.h"
#include "init.h"

void delay(uint32_t delay)
{
  	 while (delay--)
	{
		}
}

void gpioInit(void)
{
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	
	GPIOA->CRL |=  GPIO_CRL_MODE5_0 |  GPIO_CRL_MODE5_1;
	GPIOA->CRL &= ~GPIO_CRL_CNF5_0 &~ GPIO_CRL_CNF5_1;
}

void ledOn(void)
{
		GPIOA->ODR |= GPIO_ODR_ODR5;
}
