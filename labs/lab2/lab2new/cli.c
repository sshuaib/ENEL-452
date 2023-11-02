/*Salman Shuaib
	200374212
	ENEL 452
	Lab 2
*/

#include "cli.h"
#include "usart.h"

void CLI_Transmit(uint8_t *pData, uint16_t Size)
{
	for (uint16_t i = 0; i < Size; i++)
	{
		sendByte(pData[i]);
	}
}

void CLI_Receive(uint8_t *pData, uint16_t Size)
{
	uint16_t i = 0;
	while (i < Size - 1)
	{
		uint8_t data = getByte();
		if (data == 0x0A || data == 0xD)
		{
			break;
		}
		if (data == 0x08 || data == 0x7F)
		{
			if (i >0 )
			{
				sendByte(0x08);
				sendByte(0x20);
				sendByte(0x08);
				i--;
			}
			continue;
		}
		 
		
		if (data >= 0x20 && data <= 0x7E)
		{
			pData[i++] = data;
			sendByte(data);
		}
	}
	pData[i] = 0x0;
}



