/*Salman Shuaib
	200374212
	ENEL 452
	Lab 5
*/
#include "FreeRTOS.h"
#include "queue.h"
#include "task.h"
#include "init.h"
#include "usart.h"

#define mainBLINKY_TASK_PRIORITY	(tskIDLE_PRIORITY + 1)
#define CLI_TASK_PRIORITY (tskIDLE_PRIORITY + 2)

#define QUEUE_LENGTH 8
#define QUEUE_ITEM_SIZE sizeof(char)
	
QueueHandle_t usart_Queue;
QueueHandle_t cli_Queue;

static void vBlinkTask(void *parameters);
static void vCLITask(void *parameters);
void USART2_IRQHandler(void);

int main(void)
{
	usart_config();
	serial_open();
	led_init();
	
	print_message("This program allows you to alter the frequency of the the on-board LED. \n");
  print_message("\r\nEnter '1', '2', '3' to blink the on-board LED at different rates. \n");
  print_message("\r\nEach number equates to an increase in speed. 1 being slow. 2 being medium. 3 being fast.\n");
  print_message("\r\n>>  ");
	
	usart_Queue = xQueueCreate(QUEUE_LENGTH, QUEUE_ITEM_SIZE);
	cli_Queue = xQueueCreate(QUEUE_LENGTH, QUEUE_ITEM_SIZE);
	
	xTaskCreate(vBlinkTask, "Blinky", configMINIMAL_STACK_SIZE, NULL, mainBLINKY_TASK_PRIORITY, NULL);
	xTaskCreate(vCLITask, "CLI", configMINIMAL_STACK_SIZE, (void*) cli_Queue, CLI_TASK_PRIORITY, NULL);
	
	vTaskStartScheduler();
	
	return 0;
}

static void vBlinkTask(void *parameters)
{
	char rx_command;
	cli_Queue = (QueueHandle_t) parameters;
	
	for (;;)
	{
		if(xQueueReceive(cli_Queue, &rx_command, 0) != pdPASS) {}
		else {}
			
		if(rx_command == 'a')
		{
		led_on();
		vTaskDelay(1000);
		led_off();
		vTaskDelay(1000);
		}
		
		if(rx_command == 'b')
		{
		led_on();
		vTaskDelay(3000);
		led_off();
		vTaskDelay(3000);
		}
		
		if(rx_command == 'c')
		{
		led_on();
		vTaskDelay(5000);
		led_off();
		vTaskDelay(5000);
		}
	}
}

static void vCLITask(void *parameters)
{
	uint8_t command;
	usart_Queue = (QueueHandle_t) parameters;
	for(;;)
	{
		if(xQueueReceive(usart_Queue, &command, portMAX_DELAY) != pdPASS) {}
		else 
			{ 
				send_data(command, 100);
				print_message("\r\n >>  ");
				xQueueSendToFront(cli_Queue, &command, NULL);
			}
	}
}

void USART2_IRQHandler(void)
{
    if ((USART2->SR & USART_SR_RXNE))
    {
        uint8_t rx_data = USART2->DR;
        USART2->SR &= ~USART_SR_RXNE;
    }
}
