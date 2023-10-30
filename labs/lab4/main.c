/* Salman Shuaib
   200374212
   ENEL 452
   Lab 4
*/
#include "usart.h" // Include the USART library
#include "cli.h"   // Include the CLI (Command Line Interface) library
#include "init.h"  // Include the initialization library

#define STATUS_WINDOW_HEIGHT 10 // Define a constant for the status window height

int main(void)
{
    uint8_t input[100]; // Declare an array to store user input
    usart_config();     // Configure USART (Universal Synchronous Asynchronous Receiver Transmitter)
    serial_open();      // Open a serial connection
    led_init();         // Initialize the LED

    CLI_Transmit((uint8_t *)("\x1b[1;1H"), strlen("\x1b[1;1H"), 150); // Send an ANSI escape code to set cursor position
    CLI_Transmit((uint8_t *)("\x1b[10;r"), strlen("\x1b[10;r"), 150); // Send an ANSI escape code to clear a region of the terminal screen
    CLI_Transmit((uint8_t *)("\x1b[10E"), strlen("\x1b[10E"), 150);     // Send an ANSI escape code to clear a region of the terminal screen

    message("This program allows you to turn the on-board LED on and off,\n"); // Display an introductory message
    message("\r\n as well as check the status of the LED.\n");                 // Display additional instructions
    message("\r\n Enter 'Help' to find out the necessary commands.\n");       // Prompt the user for input
    message("\r\n>>  ");

    while (1) // Start an infinite loop
    {
        char* command;                    // Declare a pointer to store the user's command
        CLI_Receive(input, 100, 100);     // Receive user input via CLI (with a timeout of 10 ms)
        command = (char*) input;          // Assign the received input to the 'command' variable

        // Quit program
        if (strcmp(command, "Quit") == 0) // Check if the user's command is "Quit"
        {
            newStatus("Quit");           // Update the status
            message("\r\n Exit program \n"); // Display an exit message
            serial_close();               // Close the serial connection
            break;                        // Exit the infinite loop
        }

        // Turn on LED
        else if (strcmp(command, "Turn on") == 0) // Check if the user's command is "Turn on"
        {
            led_on();                      // Turn on the LED
            newStatus("Turn on");          // Update the status
            message("\r\n >>  ");          // Display a prompt for the next command
        }

        // Turn off LED
        else if (strcmp(command, "Turn off") == 0) // Check if the user's command is "Turn off"
        {
            led_off();                     // Turn off the LED
            newStatus("Turn off");         // Update the status
            message("\r\n >>  ");          // Display a prompt for the next command
        }

        // Check status of LED
        else if (strcmp(command, "Status") == 0) // Check if the user's command is "Status"
        {
            if (GPIOA->IDR & GPIO_IDR_IDR5)   // Check the status of the LED
            {
                newStatus("Status");        // Update the status
                message("\r\n Status: LED is on\n"); // Display the LED status
                message("\r\n >>  ");         // Display a prompt for the next command
            }
            else
            {
                message("\r\n Status: LED is off\n"); // Display the LED status
                message("\r\n >>  ");                  // Display a prompt for the next command
            }
        }

        // Print out a list explaining commands
        else if (strcmp(command, "Help") == 0) // Check if the user's command is "Help"
        {
            newStatus("Help"); // Update the status
            message("\r\n Please note, the commands are case-sensitive\n"); // Display a help message
            message("\r\n Press return (enter) after keying in a command\n"); // Display additional instructions
            message("\r\n Enter 'Help' for information on commands\n");
            message("\r\n Enter 'Turn on' to turn LED on\n");
            message("\r\n Enter 'Turn off' to turn LED off\n");
            message("\r\n Enter 'Status' to find out the status of the LED\n");
            message("\r\n Enter 'Quit' to quit the program\n");
            message("\r\n >>  "); // Display a prompt for the next command
        }
        else
        {
            newStatus("Invalid Entry"); // Update the status for an invalid entry
            message("\r\n Invalid Entry\n"); // Display a message for an invalid command
            message("\r\n >>  ");           // Display a prompt for the next command
        }
    }
}
