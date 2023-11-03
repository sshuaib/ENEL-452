/*Salman Shuaib
	200374212
	ENEL 452
	Lab 2
*/

#include "stm32f10x.h"
#include "usart.h"
#include "cli.h"
#include <string.h>

int main()
{
		uint8_t input[100];
	
    // Initialize UART
		usartConfig();
    serial_open();

    // Initialize LEDs
    ledinit();
	
	  print_message("This program allows you to turn the on-board LED on and off,\n");
    print_message("\r\n as well as check the status of the LED.\n");
    print_message("\r\n Enter 'Help' to find out the necessary commands.\n");
    print_message("\r\n>>  ");

    while (1) {
			
				char* command;
			  CLI_Receive(input, 100);
				command = (char*)input;
			
				if (strcmp(command, "Quit") == 0)
            {
                print_message("\r\n Exit program \n");
                serial_close();
                return 0; // Exit the program
            }
            else if (strcmp(command, "Turn on") == 0)
            {
                led1ON();
                print_message("\r\n >>  ");
            }
            else if (strcmp(command, "Turn off") == 0)
            {
                led1OFF();
                print_message("\r\n >>  ");
            }
            else if (strcmp(command, "Status") == 0)
            {
                if (GPIOA->IDR & GPIO_IDR_IDR5)
                {
                    print_message("\r\n Status: LED is on\n");
                }
                else
                {
                    print_message("\r\n Status: LED is off\n");
                }
                print_message("\r\n >>  ");
            }
            else if (strcmp(command, "Help") == 0)
            {
                print_message("\r\n Please note, the commands are case-sensitive\n");
                print_message("\r\n Press return(enter) after keying in the command\n");
                print_message("\r\n Enter 'Help' for information on commands\n");
                print_message("\r\n Enter 'Turn on' to turn LED on\n");
                print_message("\r\n Enter 'Turn off' to turn LED off\n");
                print_message("\r\n Enter 'Status' to find out the status of LED\n");
                print_message("\r\n Enter 'Quit' to quit the program\n");
                print_message("\r\n >>  ");
            }
            else
            {
                print_message("\r\n Invalid Entry\n");
                print_message("\r\n >>  ");
            }
    }
}
