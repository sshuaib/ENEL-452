/*Salman Shuaib
	200374212
	ENEL 452
	Lab 2
*/

#include "stm32f10x.h"
#include "usart.h"


// configuring the cpower perhiperhials
void clockInit(void){
      
        
//* enable HSI and wait for it to be ready

            RCC->CR |= RCC_CR_HSION;
    while (((RCC->CR) & (RCC_CR_HSION | RCC_CR_HSIRDY)) == 0);
                  
//* enable HSE with Bypass and wait for it to be ready

            RCC->CR |= RCC_CR_HSEON | RCC_CR_HSEBYP;
    while (((RCC->CR) & (RCC_CR_HSEON | RCC_CR_HSEBYP | RCC_CR_HSERDY)) == 0);
                        
   
////SET HSI as SYSCLK and wait for it to be recognized

//          RCC->CFGR = RCC_CFGR_SW_HSI;
//    while (((RCC->CFGR) & (RCC_CFGR_SW_HSI | RCC_CFGR_SWS_HSI)) != 0);
                  
//SET HSE as SYSCLK and wait for it to be recognized

            RCC->CFGR = RCC_CFGR_SW_HSE;
    while (((RCC->CFGR) & (RCC_CFGR_SW_HSE | RCC_CFGR_SWS_HSE)) == 0);

//****************To Use PLL as SYSCLK    
// Disable PLL.
            
            RCC->CR &= ~RCC_CR_PLLON;
            RCC->CFGR = 0x00050000;// 24 MHz

//ENABLE PLL and wait for it to be ready

    RCC->CR |= RCC_CR_PLLON;
    while (((RCC->CR) & (RCC_CR_PLLON | RCC_CR_PLLRDY)) == 0);
            
// Set PLL as SYSCLK and wait for it to be ready
                  
    RCC->CFGR |= RCC_CFGR_SW_PLL;// 0x00000002;
    while (((RCC->CFGR) & (RCC_CFGR_SW_PLL | RCC_CFGR_SWS_PLL)) == 0);
           
}

void serialOpen(void) {
			//clock config
			RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
	
			USART1->BRR |= 0x138;
			USART1->CR1 |= USART_CR1_TE | USART_CR1_RE | USART_CR1_UE;
	
	//Enable Port A and B *
      RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_AFIOEN;
			
		// Configure PA2 (TX) as alternate function output push-pull, max speed 50 MHz
		GPIOA->CRL &= ~(GPIO_CRL_CNF2_0);
		GPIOA->CRL |= GPIO_CRL_CNF2_1 | GPIO_CRL_MODE2;

		// Configure PA3 (RX) as input with pull-up/pull-down
		GPIOA->CRL &= ~(GPIO_CRL_CNF3_0 | GPIO_CRL_MODE3);
		GPIOA->CRL |= GPIO_CRL_CNF3_1;
}
			
int send(uint8_t info)
{
	if(!(USART2->CR1 & USART_CR1_UE))
	{
		return 1;
	}
	if(!(USART1->SR & USART_SR_TXE))
	{
		
	}
	USART1->DR = info;
	return 0;
}

uint8_t receive(void)
{
	uint8_t data;
	if((USART1->SR & USART_SR_RXNE))
	{
		data = USART1->DR;
	}
	return data;
}

char getbyte(void)
{
	while(!(USART2->SR & USART_SR_RXNE));
	
	return (char)(USART2->DR);
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
