/*Salman Shuaib
	200374212
	ENEL 452
	Lab 4
*/

#ifndef USART_H
#define USART_H

#include "stm32f10x.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define RX_BUFFER_SIZE 100

extern volatile uint8_t rx_buffer[];
extern volatile uint8_t rx_buffer_head;
extern volatile uint8_t rx_buffer_tail;

void timer2_init(uint32_t timeout);
void usart_config(void);
void serial_open(void);
void serial_close(void);
int send_data(uint8_t data, uint32_t timeout);
uint8_t receive_data(uint32_t timeout);
void USART2_IRQHandler(void);

#endif
