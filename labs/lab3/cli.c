/*Salman Shuaib
	200374212
	ENEL 452
	Lab 3
*/

#include "usart.h"
#include "cli.h"
#include "init.h"

void CLI_Transmit(uint8_t *pData, uint16_t Size, uint32_t timeout)
{
    for (uint16_t i = 0; i < Size; i++)
    {
        send_data(pData[i], timeout);
    }
}

void CLI_Receive(uint8_t *pData, uint16_t Size, uint32_t timeout)
{
    uint16_t i = 0;
    while (i < Size - 1)
    {
        if (rx_buffer_head != rx_buffer_tail)
        {
            uint8_t data = rx_buffer[rx_buffer_tail];
            rx_buffer_tail = (rx_buffer_tail + 1) % RX_BUFFER_SIZE;

            // If a new line character or carriage return is received, break
            if (data == 0x0A || data == 0x0D)
                break;
            
            // Handle backspace and delete character 
            if (data == 0x08 || data == 0x7F)
            {
                if (i > 0)
                {
                    // Timeout is 10 ms
                    send_data(0x08, 100); // Move cursor one space back
                    send_data(0x20, 100); // Replace with space
                    send_data(0x08, 100); // Move cursor back again
                    i--;
                }
                continue;
            }
            
            if (data >= 0x20 && data <= 0x7E)
            {
                pData[i++] = data;
                send_data(data, timeout); // Echo received data
            }
        }
    }
    pData[i] = 0x00;
}
