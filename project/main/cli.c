/* Salman Shuaib 200374212 ENEL 452 Lab 5 */

#include "usart.h"
#include "cli.h"
#include "init.h"

volatile uint8_t rx_buffer[RX_BUFFER_SIZE]; /* Circular receive buffer */
volatile uint8_t rx_buffer_head = 0; /* Head index of receive buffer */
volatile uint8_t rx_buffer_tail = 0; /* Tail index of receive buffer */

/**
 * @brief Transmits data to the Command Line Interface (CLI).
 * 
 * @param pData Pointer to the data to be transmitted.
 * @param Size Size of the data to be transmitted.
 * @param timeout Timeout for the transmission operation.
 */
 
void CLI_Transmit(uint8_t *pData, uint16_t Size, uint32_t timeout)
{
    for (uint16_t i = 0; i < Size; i++)
    {
        send_data(pData[i], timeout);
    }
}

/**
 * @brief Receives data from the Command Line Interface (CLI).
 * 
 * @param pData Pointer to the buffer to store received data.
 * @param Size Size of the buffer.
 * @param timeout Timeout for the reception operation.
 */

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
            {
                pData[i] = 0x00; // Null-terminate the string
                send_data('\r', timeout); // Echo the carriage return
                send_data('\n', timeout); // Echo the line feed
                break;
            }

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

/**
 * @brief Displays a new status statement on the Command Line Interface (CLI) window.
 * 
 * This function sets the cursor position to the home position, clears the line, displays the status
 * statement, and then scrolls the window.
 * 
 * @param statement The status statement to be displayed.
 */

void newStatus(const char *statement)
{
    uint32_t timeout = 100; // Set an appropriate timeout value

    // Save the cursor position, move to the home position, and display the status statement
    CLI_Transmit(ANSI_CURSOR_SAVE, strlen(ANSI_CURSOR_SAVE), timeout);
    CLI_Transmit(ANSI_CURSOR_HOME, strlen(ANSI_CURSOR_HOME), timeout);
    CLI_Transmit(ANSI_CLEAR_LINE, strlen(ANSI_CLEAR_LINE), timeout);
    CLI_Transmit((uint8_t *)statement, strlen(statement), timeout);

    // Scroll the window and restore the cursor position
    CLI_Transmit(ANSI_CURSOR_RESTORE, strlen(ANSI_CURSOR_RESTORE), timeout);

    print_message(print_message);
}
