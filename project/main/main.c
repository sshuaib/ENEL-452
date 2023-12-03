#include <stdio.h>
#include <stdbool.h>

//#include "stm32F103RB.h"
#include "FreeRTOS.h"
#include "queue.h"
#include "task.h"
#include "init.h"
#include "cli.h"
#include "usart.h"

#define STATUS_WINDOW_HEIGHT 10 // Define a constant for the status window height

#define mainEXTERNAL_TASK_PRIORITY 		(tskIDLE_PRIORITY + 1 )
#define mainINTERNAL_TASK_PRIORITY 		(tskIDLE_PRIORITY + 1 )
#define CLI_TASK_PRIORITY		(tskIDLE_PRIORITY + 2 )
//#define configMAX_SYSCALL_INTERRUPT_PRIORITY 16


#define QUEUE_LENGTH 10
#define QUEUE_ITEM_SIZE sizeof(char)
	
QueueHandle_t usartQueue;
QueueHandle_t cliQueue;

int idleFloor = 1;

static void vExternalTask( void * parameters);
static void vInternalTask( void * parameters);
static void vCLITask( void * parameters);
void USART2_IRQHandler(void);
void EXTI15_10_IRQHandler(void);

int main(void)
{
	uint8_t input[100];
	serial_open();
	usart_config();
	led_init();
	initInterrupt();
	
	CLI_Transmit((uint8_t *)("\x1b[1;1H"), strlen("\x1b[1;1H"), 150); // Send an ANSI escape code to set cursor position
  CLI_Transmit((uint8_t *)("\x1b[10;r"), strlen("\x1b[10;r"), 150); // Send an ANSI escape code to clear a region of the terminal screen
  CLI_Transmit((uint8_t *)("\x1b[10E"), strlen("\x1b[10E"), 150);     // Send an ANSI escape code to clear a region of the terminal screen

	print_message(" >>>>>> Elevator Control System <<<<<< \n");
	print_message("\r\n Enter 'D' to go down.\n");
	print_message("\r\n Enter 'U' to go up.\n");
	//print_message("\r\n Enter '1' to go to the first floor.\n");
	//print_message("\r\n Enter '2' to go to the second floor.\n");
	//print_message("\r\n Enter '3' to go to the third floor.\n");
	//print_message("\r\n Enter 'm' to enter Maintenance mode.\n");
	//print_message("\r\n Type 'Status' for the current status of the elevator.\n");
	print_message("\r\n >>  ");
	
	// Create a queue for USART data
  usartQueue = xQueueCreate(QUEUE_LENGTH, QUEUE_ITEM_SIZE);
  // Create a queue to send data from CLI task to the main task
  cliQueue = xQueueCreate(QUEUE_LENGTH, QUEUE_ITEM_SIZE);
	
	/*
		char* command;                    // Declare a pointer to store the user's command
    CLI_Receive(input, 100, 100);     // Receive user input via CLI (with a timeout of 10 ms)
    command = (char*) input;        // Assign the received input to the 'command' variable
		

		while(1){
		if (strcmp(command, "Quit") == 0) 													 // Check if the user's command is "2"
    {		
            newStatus("Quit");           // Update the status
            print_message("\r\n Exit program \n"); // Display an exit message
            serial_close();               // Close the serial connection
            break;  
    }
		else if (strcmp(command, "1") == 0) // Check if the user's command is "Turn on"
     {
            led_on();                      // Turn on the LED
            newStatus("You are currently on Floor 1");          // Update the status
            print_message("\r\n >>  ");          // Display a prompt for the next command
     }
		 
		 else if (strcmp(command, "2") == 0) // Check if the user's command is "Turn on"
     {
            led_on();                      // Turn on the LED
            newStatus("You are currently on Floor 2");          // Update the status
            print_message("\r\n >>  ");          // Display a prompt for the next command
     }
		 
		 else if (strcmp(command, "3") == 0) // Check if the user's command is "Turn on"
     {
            led_on();                      // Turn on the LED
            newStatus("You are currently on Floor 3");          // Update the status
            print_message("\r\n >>  ");          // Display a prompt for the next command
     }
		
     else if (strcmp(command, "Help") == 0) // Check if the user's command is "Help"
     {
          newStatus("Help"); // Update the status
          print_message("\r\n Please note, the commands are case-sensitive\n"); // Display a help message
          print_message("\r\n Press return (Enter) after keying in a command\n"); // Display additional instructions
          print_message("\r\n Enter 'Help' for information on commands\n");
          print_message("\r\n Enter 'Status' to find out the status of the LED\n");
          print_message("\r\n Enter 'Quit' to quit the program\n");
          print_message("\r\n >>  "); // Display a prompt for the next command
		 }
		 else if (strcmp(command, "Status") == 0) // Check if the user's command is "Status"
     {
					if (GPIOA->IDR & GPIO_IDR_IDR5)   // Check the status of the LED
            {
                newStatus("Status");        // Update the status
                print_message("\r\n Status: You are currently on Floor 2.\n"); // Display the LED status
                print_message("\r\n >>  ");         // Display a prompt for the next command
            }
            else
            {
                print_message("\r\n Status: Work in progress.\n"); // Display the LED status
                print_message("\r\n >>  ");                  // Display a prompt for the next command
            }
     }
    else
    {
        newStatus("Invalid Entry"); // Update the status for an invalid entry
        print_message("\r\n Invalid Entry\n"); // Display a message for an invalid command
        print_message("\r\n >>  ");           // Display a prompt for the next command
    }
	}
	*/
	
	xTaskCreate(vExternalTask, "Blinky", configMINIMAL_STACK_SIZE, (void*) cliQueue, mainEXTERNAL_TASK_PRIORITY, NULL);
	xTaskCreate(vInternalTask, "Button", configMINIMAL_STACK_SIZE, (void*) cliQueue, mainINTERNAL_TASK_PRIORITY, NULL);
  xTaskCreate(vCLITask, "CLI", configMINIMAL_STACK_SIZE, (void*) usartQueue, CLI_TASK_PRIORITY, NULL);
	
	/* Start the scheduler. */
	vTaskStartScheduler();
	
	return 0;
}

static void vExternalTask( void * parameters)
{
	char rx_command;
	cliQueue = (QueueHandle_t) parameters;
	
	for(;;)
	{
		if(xQueueReceive(cliQueue, &rx_command, portMAX_DELAY) == pdPASS)
		{
		if(rx_command == 'u')
		{
			if(idleFloor < 3)
			{
					led_on();
					newStatus("Elevator is on the way...");
					vTaskDelay(1000);
				
					led_off();
					newStatus("Elevator is here!");
					vTaskDelay(1000);
					print_message("\r\n Elevator doors are open, please enter. \n"); 
					idleFloor++;
			}
			else
			{
				newStatus("Elevator is at highest floor.");
			}
		}
		else if(rx_command == 'd')
		{
			if(idleFloor > 1)
			{
					led_on();
					newStatus("Elevator is on the way...");
					vTaskDelay(1000);
					
					led_off();
					newStatus("Elevator is here!");
					print_message("\r\n Elevator doors are open, please enter. \n"); 
					vTaskDelay(1000);
					idleFloor--;
			}
		}
			else
			{
				newStatus("Elevator is at the ground floor.");
			}
			
	}
}
	}

static void vInternalTask( void * parameters)
{
	cliQueue = (QueueHandle_t)parameters;
	for (;;)
	{
		char internalCommand;
		
		if(xQueueReceive(cliQueue, &internalCommand, portMAX_DELAY) == pdPASS)
		{
			if (internalCommand >= '1' && internalCommand <= '3')
			{
				int floorChoice = internalCommand - '0';
				
				if (floorChoice != idleFloor)
				{
					char message[50];
					snprintf(message, sizeof(message), "Elevator is moving to Floor %d", floorChoice);
					newStatus(message);
					
					while (idleFloor != floorChoice)
					{
						if (idleFloor < floorChoice)
						{
							idleFloor++;
							vTaskDelay(1000);
						}
						else if(idleFloor > floorChoice)
						{
							idleFloor --;
							vTaskDelay(1000);
						}
						snprintf(message, sizeof(message), "Elevator is moving to Floor %d", idleFloor);
						newStatus(message);
					}
				}
				
				else 
				{
					char message[50];
          snprintf(message, sizeof(message), "Already at Floor %d", floorChoice);
          newStatus(message);
				}
			}
						else if (internalCommand == 'm')
            {
                // Enter maintenance mode actions
                newStatus("Entering Maintenance Mode");
                // Perform maintenance mode actions here
                print_message("\r\n Maintenance Mode: Performing maintenance tasks...\n");
                vTaskDelay(2000);  // Delay for demonstration purposes, adjust as needed
                print_message("\r\n Maintenance Mode: Tasks completed.\n");
                newStatus("Maintenance Mode Complete");
            }
		}
	}
}


static void vCLITask(void *parameters) 
{
	uint8_t command;
	usartQueue = (QueueHandle_t) parameters;
	for(;;)
	{
		if(xQueueReceive(usartQueue, &command, portMAX_DELAY) != pdPASS) {}
		else
			{
				send_data(command, 100);
				
				print_message("\r\n ");
				xQueueSendToFront(cliQueue, &command, NULL);
			}
	}
    
}

/**ISR for USART2 receive*/
void USART2_IRQHandler(void)
{
    if (USART2->SR & USART_SR_RXNE)
    {
        uint8_t rx_data = USART2->DR;

        // Check if the received character is a valid ASCII character
        if (rx_data >= 32 && rx_data <= 126)
        {
            xQueueSendToFrontFromISR(usartQueue, &rx_data, NULL);
        }
        // Clear the RXNE flag
        USART2->SR &= ~USART_SR_RXNE;
    }
}
bool push_button = true;
void EXTI15_10_IRQHandler(void)
{
		if (EXTI->PR & EXTI_PR_PR13)
		{
			if(push_button == true)
		{
		led_on();
		 newStatus("EMERGENCY");
		push_button = false;
		}
		else if(push_button == false)
		{
		led_off();
		newStatus("NOW OPERATIONAL");
		push_button = true;
		}
		}

EXTI->PR |= EXTI_PR_PR13;
}
