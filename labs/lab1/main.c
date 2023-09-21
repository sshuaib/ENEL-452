#include "stm32f10x.h"
#include "init.h"

int main()
{
	gpioInit();	
	ledOn();
	
	while(1) // Turn on PA5 led
	{
		GPIOA->ODR |= GPIO_ODR_ODR5;//turn on
		delay(3500000);
		GPIOA->ODR &= (uint32_t) ~GPIO_ODR_ODR5;//turn off
		delay(3500000);
	}
	
	return 0;
}