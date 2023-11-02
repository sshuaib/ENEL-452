/*Salman Shuaib
	200374212
	ENEL 452
	Lab 2
*/

#include "stm32f10x.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "cli.h"

void clockInit(void);
void usartConfig(void);
void serial_open(void);
void serial_close(void);

int sendByte(uint8_t c);
uint8_t getByte(void);

void delay(uint32_t);

void led1ON(void);
void led1OFF(void);
void ledinit(void);

void print_message(char message[]);

#define NUC_GREEN_ON 0x00000020;
#define NUC_GREEN_OFF 0x00200000;
