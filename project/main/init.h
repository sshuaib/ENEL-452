/*Salman Shuaib
	200374212
	ENEL 452
	Lab 5
*/

#include "stm32f10x.h"
#include <string.h>
#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

void led_init(void);
void initInterrupt(void);
void redled_on(void);
void redled_off(void);
void led_on(void);
void led_off(void);
void print_message(char message[]);
