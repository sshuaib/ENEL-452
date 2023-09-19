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
	GPIOA->CRH &= ~(GPIO_CRL_CNF5);
	
	GPIOA->CRL |=  GPIO_CRL_MODE5_0 |  GPIO_CRL_MODE5_1;
	GPIOA->CRL &= ~GPIO_CRL_CNF6_0 &~ GPIO_CRL_CNF6_1;
}

void ledOn(void)
{
		GPIOA->ODR |= GPIO_ODR_ODR5;
}
