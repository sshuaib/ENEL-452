
#include "usart.h" 
#include "cli.h"   
#include "init.h"  

// Transmit data over the communication interface
void CLI_Transmit(uint8_t *pData, uint16_t Size, uint32_t timeout)
{
    for (uint16_t i = 0; i < Size; i++)
    {
        send_data(pData[i], timeout); // Send each byte of data using the send_data function
    }
}

// Receive data from the communication interface
void CLI_Receive(uint8_t *pData, uint16_t Size, uint32_t timeout)
{
    uint16_t i = 0;
    while (i < Size - 1)
    {
        if (rx_buffer_head != rx_buffer_tail)
        {
            uint8_t data = rx_buffer[rx_buffer_tail];
            rx_buffer_tail = (rx_buffer_tail + 1) % RX_BUFFER_SIZE;

            // Check for special control characters
            // If a new line character or carriage return is received, break the loop
            if (data == 0x0A || data == 0x0D)
                break;

            // Handle backspace and delete characters
            if (data == 0x08 || data == 0x7F)
            {
                if (i > 0)
                {
                    // Timeout is 10 ms
                    send_data(0x08, 100); // Move the cursor one space back
                    send_data(0x20, 100); // Replace with a space
                    send_data(0x08, 100); // Move the cursor back again
                    i--;
                }
                continue;
            }

            // Check if the received data is within the printable ASCII range
            if (data >= 0x20 && data <= 0x7E)
            {
                pData[i++] = data;       // Store the printable character
                send_data(data, timeout); // Echo the received data
            }
        }
    }
    pData[i] = 0x00; // Null-terminate the received data string
}

// Update the status message on the screen
void newStatus(const char* statement)
{
    uint32_t timeout = 100; // Set an appropriate timeout value

    // Save the cursor position, move to the home position, and display the status statement
    CLI_Transmit(ANSI_CURSOR_SAVE, strlen(ANSI_CURSOR_SAVE), timeout);
    CLI_Transmit(ANSI_CURSOR_HOME, strlen(ANSI_CURSOR_HOME), timeout);
	  CLI_Transmit(ANSI_CLEAR_LINE, strlen(ANSI_CLEAR_LINE), timeout);
    CLI_Transmit((uint8_t *)statement, strlen(statement), timeout);

    // Scroll the window and restore the cursor position
    CLI_Transmit(ANSI_CURSOR_RESTORE, strlen(ANSI_CURSOR_RESTORE), timeout);
	
		message(message);
}
