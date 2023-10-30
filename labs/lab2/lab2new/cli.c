/*Salman Shuaib
	200374212
	ENEL 452
	Lab 2
*/

#include "stm32f10x.h"
#include "cli.h"
#include "usart.h"

void CLI_Transmit(uint8_t *pData, uint16_t size)
{
	for (uint16_t i = 0; i < size; i++)
	{
		send(pData[i]);
	}
}

void CLI_Receive(uint8_t *pData, uint16_t Size) {
    uint8_t receivedChar;
    uint16_t receivedIndex = 0;
    char commandBuffer[50]; // Buffer to store received command

    while (receivedIndex < Size - 1) { // Leave space for null-terminator
        receivedChar = getbyte();
        send(receivedChar); // Echo the received character

        if (receivedChar == '\r' || receivedChar == '\n') {
            // End of command, null-terminate the string
            pData[receivedIndex] = '\0';

            // Process the received command using a switch statement
            switch (commandBuffer[0]) {
							case 'L':
                    if (strncmp(commandBuffer, "LED on", strlen("LED on")) == 0) {
                        // Turn on the LED
                        led1ON();
                        CLI_Transmit((uint8_t *)"LED is now ON.\n", 16);
                    } else if (strncmp(commandBuffer, "LED off", strlen("LED off")) == 0) {
                        // Turn off the LED
                        led1OFF();
                        CLI_Transmit((uint8_t *)"LED is now OFF.\n", 17);
                    } else if (strncmp(commandBuffer, "LED status", strlen("LED status")) == 0) {
                        // Query the state of the LED
                        int ledStatus = GPIOA_ODR_Read(NUC_GREEN_ON;);
                        if (ledStatus) {
                            CLI_Transmit((uint8_t *)"LED is ON.\n", 12);
                        } else {
                            CLI_Transmit((uint8_t *)"LED is OFF.\n", 13);
                        }
                    } else {
                        // Invalid LED-related command
                        CLI_Transmit((uint8_t *)"Invalid LED command. Type 'help' for available commands.\n", 63);
                    }
                    break;

                case 'h':
                    if (strncmp(commandBuffer, "help", strlen("help")) == 0) {
                        // Print help text explaining the available commands
                        char helpText[] = "Available commands:\n"
                                          "1. LED on - Turn on the LED.\n"
                                          "2. LED off - Turn off the LED.\n"
                                          "3. LED status - Query the state of the LED.\n"
                                          "4. help - Display this help message.\n";
                        CLI_Transmit((uint8_t *)helpText, strlen(helpText));
                    } else {
                        // Invalid help-related command
                        CLI_Transmit((uint8_t *)"Invalid help command. Type 'help' for available commands.\n", 66);
                    }
                    break;

                default:
                    // Invalid command
                    CLI_Transmit((uint8_t *)"Invalid command. Type 'help' for available commands.\n", 54);
            }

            // Reset the command buffer
            //memset(commandBuffer, 0, sizeof(commandBuffer));

            break;
        }

        // Store the received character in the command buffer
        commandBuffer[receivedIndex] = receivedChar;
        receivedIndex++;
    }
}
