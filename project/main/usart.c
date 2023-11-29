/*Salman Shuaib
	200374212
	ENEL 452
	Lab 5
*/

#include "usart.h" /* Include USART library */
#include "cli.h" /* Include CLI library */
#include <string.h>

void timer2_init(uint32_t timeout)
{
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN; /* Enable Timer2 */
    TIM2->CR1 |= TIM_CR1_CEN; /* Enable Timer2 */
    TIM2->EGR |= TIM_EGR_UG; /* Reinitialize the counter */
    TIM2->PSC = 0x1DAF; /* Divide 76 MHz by 7600 (PSC+1), PSC_CLK = 10000 Hz, 1 count = 0.1 ms */
    TIM2->ARR = timeout; /* 100 counts = 10 ms or 100 Hz */
    TIM2->SR = 0;
    TIM2->CR1 |= TIM_CR1_ARPE | TIM_CR1_CEN; /* Enable Timer3 */
}

void usart_config(void)
{
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_AFIOEN; /* Enable AFIO and Port A */
    
    GPIOA->CRL |= GPIO_CRL_CNF2_1 | GPIO_CRL_MODE2; /* Configuring PA2 for alternate function output push-pull, max speed 50 MHz */
    GPIOA->CRL &= ~GPIO_CRL_CNF2_0;
    
    GPIOA->CRL |= GPIO_CRL_CNF3_1; /* Configuring PA3 as input pull-up/pull down */
    GPIOA->CRL &= ~GPIO_CRL_CNF3_0 & ~GPIO_CRL_MODE3;
}

void serial_open(void)
{
    RCC->APB1ENR |= RCC_APB1ENR_USART2EN; /* Enable USART2 clock */
    
    USART2->CR1 |= USART_CR1_UE; /* Enable USART */
    
    USART2->BRR |= 0x0139; /* Set baud rate to 9600 */
    
    USART2->CR1 |= USART_CR1_RE | USART_CR1_TE | USART_CR1_UE; /* Enable receiving and transmitting */
    USART2->CR2 &= ~USART_CR2_STOP; /* 1 stop bit */
    USART2->CR1 |= USART_CR1_M; /* Set word length to 8 data bits */
    USART2->CR1 |= USART_CR1_RXNEIE; /* Enable USART2 receive interrupt */
    NVIC_EnableIRQ(USART2_IRQn); /* Enable USART2 interrupt */
}

void serial_close(void)
{
    RCC->APB1ENR &= ~RCC_APB1ENR_USART2EN; /* Disable USART2 clock */
    USART2->CR1 = 0;
    USART2->BRR = 0; /* Clear USART2 configuration */
}

int send_data(uint8_t data, uint32_t timeout)
{
    if (!(USART2->CR1 & USART_CR1_UE))
    {
        return 1; /* Return error code 1 */
    }
    
    timer2_init(timeout);
    
    while (!(USART2->SR & USART_SR_TC)) /* Wait until TC flag is set */
    {
        if ((TIM2->SR & TIM_SR_UIF)) /* Check if timeout is expired */
        {
            return 2; /* Return error code 2 */
        }
    }
    
    USART2->DR = data;
    
    if (!(USART2->SR & USART_SR_TXE))
    {
        return 1; /* Return error code 1 */
    }
    
    return 0; /* Return success code 0 */
}

uint8_t receive_data(uint32_t timeout)
{
    uint8_t value;
    timer2_init(timeout);
    
    while (!(USART2->SR & USART_SR_TC)) /* Wait until TC flag is set */
    {
        if ((TIM2->SR & TIM_SR_UIF)) /* Check if timeout is expired */
        {
            return 2; /* Return error code 2 */
        }
    }
    
    if (!(USART2->SR & USART_SR_RXNE))
    {
    }
    value = USART2->DR;
    return value;
}
