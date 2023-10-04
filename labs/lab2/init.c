#include "stm32f10x.h"
#include "init.h"



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
            
//Enable Port A and B *
      RCC->APB2ENR |= RCC_APB2ENR_IOPAEN |RCC_APB2ENR_IOPBEN | RCC_APB2ENR_AFIOEN | RCC_APB2ENR_ADC1EN |RCC_APB2ENR_IOPCEN;
			
// Configure PA2 (TX) as alternate function output push-pull, max speed 50 MHz
GPIOA->CRL &= ~(GPIO_CRL_CNF2 | GPIO_CRL_MODE2);
GPIOA->CRL |= GPIO_CRL_CNF2_1 | GPIO_CRL_MODE2;

// Configure PA3 (RX) as input with pull-up/pull-down
GPIOA->CRL &= ~(GPIO_CRL_CNF3 | GPIO_CRL_MODE3);
GPIOA->CRL |= GPIO_CRL_CNF3_0;
GPIOA->ODR |= GPIO_ODR_ODR3; 	// Pull-up
}


void tim3_IO_init(void){
      
      RCC->APB1ENR |= RCC_APB1ENR_TIM3EN | RCC_APB2ENR_IOPAEN;
      GPIOA->CRL |= GPIO_CRL_CNF6_1 | GPIO_CRL_MODE6;
      GPIOA->CRL &= ~GPIO_CRL_CNF6_0;

}

void configUSARTsetup(void) {
	
			RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_AFIOEN | RCC_APB2ENR_USART1EN;		//clock config
			RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
			GPIOA->CRH |= GPIO_CRH_CNF9_1 | GPIO_CRH_MODE9;																	//port config
			GPIOA->CRH &= GPIO_CRH_CNF9_0;
			GPIOA->CRH |= GPIO_CRH_CNF10_1 | GPIO_CRH_MODE10;
			GPIOA->CRH &= GPIO_CRH_CNF10_0;
	
			USART1->BRR |= 0x271;
			USART1->CR1 |= USART_CR1_TE | USART_CR1_RE | USART_CR1_UE;
}
			
void send(uint8_t info)
{
	if(!(USART1->SR & USART_SR_TXE))
	{
	}
	USART1->DR = info;
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
	GPIOA->BSRR = NUC_GREEN_ON;
}

void led1OFF(void)
{
	//GPIOA->ODR &= ~ GPIO_ODR_ODR5;
	GPIOA->BSRR = NUC_GREEN_OFF;
}

/*
void tim3GPIOSetup(uint16_t dCycleVal)
{
      // Enabling timer 3
      TIM3 ->CR1 |= TIM_CR1_CEN;
      
      //Re intializing the counter
      TIM3 -> EGR |= TIM_EGR_UG;
      
      //PWM Mode 1
      TIM3->CCMR1 |= TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1;
      
      //Preload Enable, Fast Enable
      TIM3->CCMR1 |= TIM_CCMR1_OC1PE | TIM_CCMR1_OC1FE;
      
      //Enable CH1
      TIM3->CCER |= TIM_CCER_CC1E;
      
      // Divide 24 MHz by 2400 (PSC+1), PSC_CLK= 10000 Hz, 1 count = 0.1 ms
      TIM3->PSC = 0x095F;
      
      // 100 counts = 10 ms or 100 Hz
      TIM3->ARR = 100;
      
      // 50 counts = 5 ms = 50% duty cycle
      TIM3->CCR1 = dCycleVal;
      
      // Enable Timer3
      TIM3->CR1 |= TIM_CR1_ARPE | TIM_CR1_CEN;  
}

void blueButton(void)
{
	if ((GPIOC->IDR & GPIO_IDR_IDR13)== 0)
	{
		tim3GPIOSetup(40);
	}
}
*/
