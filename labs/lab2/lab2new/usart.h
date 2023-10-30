/*Salman Shuaib
	200374212
	ENEL 452
	Lab 2
*/

#include "stm32f10x.h"
#include <stdint.h>

void clockInit(void);
void serialOpen(void);
int send(uint8_t);
uint8_t receive(void);
char getbyte(void);
void delay(uint32_t);
void led1ON(void);
void led1OFF(void);
void ledinit(void);

#define NUC_GREEN_ON 0x00000020;
#define NUC_GREEN_OFF 0x00200000;
