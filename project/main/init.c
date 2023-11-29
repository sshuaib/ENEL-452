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
	   // Configure PA0 as input with pull-up
    GPIOA->CRL &= ~GPIO_CRL_MODE0;
    GPIOA->CRL &= ~GPIO_CRL_CNF0;
    GPIOA->CRL |= GPIO_CRL_CNF0_1; // Input pull-up
	
		// Connect EXTI0 line to PA0
    AFIO->EXTICR[0] &= ~AFIO_EXTICR1_EXTI0;

    // Configure EXTI0 to trigger on rising edge
    EXTI->RTSR |= EXTI_RTSR_TR0;

    // Enable EXTI0 interrupt
    EXTI->IMR |= EXTI_IMR_MR0;

    // Set priority for EXTI0_IRQn
    NVIC_SetPriority(EXTI0_IRQn, configMAX_SYSCALL_INTERRUPT_PRIORITY);
    NVIC_EnableIRQ(EXTI0_IRQn);
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
