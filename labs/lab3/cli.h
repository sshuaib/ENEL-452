/*Salman Shuaib
	200374212
	ENEL 452
	Lab 3
*/

#include "stm32f10x.h"
#include "string.h"
#include "ctype.h"
#include "stdint.h"
#include "stdio.h"
#include "stdlib.h"

void CLI_Init(void);
void CLI_Transmit(uint8_t *pData, uint16_t Size, uint16_t timeout);
void CLI_Receive(uint8_t *pData, uint16_t Size, uint16_t timeout);
