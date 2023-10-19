/*Salman Shuaib
	200374212
	ENEL 452
	Lab 3
*/

#include "usart.h"
#include "cli.h"
#include "init.h"

int main(void)
{
    uint8_t input[100];
    usart_config();
    serial_open();
    led_init();

    message("This program allows you to turn the on-board LED on and off,\n");
    message("\r\n as well as check the status of the LED.\n");
    message("\r\n Enter 'Help' to find out the necessary commands.\n");
    message("\r\n>>  ");

    while (1)
    {
        char* command;
        CLI_Receive(input, 100, 100); // timeout is 10 ms
        command = (char*)input;

        while (1)
        {
            if (strcmp(command, "Quit") == 0)
            {
                message("\r\n Exit program \n");
                serial_close();
                return 0; // Exit the program
            }
            else if (strcmp(command, "Turn on") == 0)
            {
                led_on();
                message("\r\n >>  ");
                break;
            }
            else if (strcmp(command, "Turn off") == 0)
            {
                led_off();
                message("\r\n >>  ");
                break;
            }
            else if (strcmp(command, "Status") == 0)
            {
                if (GPIOA->IDR & GPIO_IDR_IDR5)
                {
                    message("\r\n Status: LED is on\n");
                }
                else
                {
                    message("\r\n Status: LED is off\n");
                }
                message("\r\n >>  ");
                break;
            }
            else if (strcmp(command, "Help") == 0)
            {
                message("\r\n Please note, the commands are case-sensitive\n");
                message("\r\n Press return(enter) after keying in the command\n");
                message("\r\n Enter 'Help' for information on commands\n");
                message("\r\n Enter 'Turn on' to turn LED on\n");
                message("\r\n Enter 'Turn off' to turn LED off\n");
                message("\r\n Enter 'Status' to find out the status of LED\n");
                message("\r\n Enter 'Quit' to quit the program\n");
                message("\r\n >>  ");
                break;
            }
            else
            {
                message("\r\n Invalid Entry\n");
                message("\r\n >>  ");
                break;
            }
        }
    }
}

 
