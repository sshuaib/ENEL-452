

#include "stm32f10x.h"
#include "string.h"
#include "ctype.h"
#include "stdint.h"
#include "stdio.h"
#include "stdlib.h"

#define ANSI_CLEAR_SCREEN "\x1b[2J"
#define ANSI_CURSOR_HOME "\x1b[0;0H"
#define ANSI_SCROLL_WINDOW "\x1b[10;r"

#define ANSI_CLEARSCREEN "\xlb[2J"
#define ANSI_CLEAR_LINE "\033[2K"

#define ANSI_CURSOR_UP_LINE "\x1b[A"
#define ANSI_CURSOR_DOWN_LINE "\x1b[B"
#define ANSI_CURSOR_SAVE "\x1b[s"
#define ANSI_CURSOR_RESTORE "\x1b[u"

void clearScreen(void);
void setCursorPosition(int row, int col);
void createScrollableWindow(int startRow, int endRow);

void CLI_Init(void);
void CLI_Transmit(uint8_t *pData, uint16_t Size, uint32_t timeout); // Update the parameter type for 'timeout'
void CLI_Receive(uint8_t *pData, uint16_t Size, uint32_t timeout); // Update the parameter type for 'timeout'
void newStatus(const char* statement);
