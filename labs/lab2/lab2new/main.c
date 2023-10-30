/*Salman Shuaib
	200374212
	ENEL 452
	Lab 2
*/

#include "stm32f10x.h"
#include "usart.h"
#include "cli.h"

int main()
{
    // Initialize clock (assuming it's defined in usart.h)
    // clockInit();

    // Initialize UART (assuming it's defined in usart.h)
    serialOpen();

    // Initialize LEDs (assuming it's defined in usart.h)
    ledinit();

    // Send a byte (0x21) via UART
    uint8_t num_count = 0x21;
    send(num_count);

    // Receive a byte via UART (not stored or used)
    receive();

    while (1) {
        // Data to be transmitted
        uint8_t sendData[] = "hello,world! \n";
        
        // Buffer to receive data
        uint8_t receiveData[50];

        // Transmit the data via CLI_Transmit
        CLI_Transmit(sendData, sizeof(sendData));

        // Receive data via CLI_Receive
        CLI_Receive(receiveData, sizeof(receiveData));
    }
}
