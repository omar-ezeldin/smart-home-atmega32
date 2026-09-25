/*==========================================
  LCD.h
  LCD Driver
============================================
  Type           : Driver Header
  Author         : Omar Ezzeldin
==========================================*/

#include "LIB/STD_TYPES.h"
#include "MCAL/DIO.h"

#ifndef LCD_H_
#define LCD_H_

/*==========================================
PORTS & PINS CONFIGURATION
==========================================*/

#define LCD_CONTROL_PORT PD
#define LCD_DATA_PORT    PC

#define LCD_RS P0
#define LCD_E  P1

#define LCD_D0 P0
#define LCD_D1 P1
#define LCD_D2 P2
#define LCD_D3 P3
#define LCD_D4 P4
#define LCD_D5 P5
#define LCD_D6 P6
#define LCD_D7 P7

/*==========================================
COMMANDS FUNCTIONS PROTOTYPES
==========================================*/

/**
 * @brief Returns the clear instruction code
 */
u8 LCD_CMD_CLR();

/**
 * @brief Returns the home instruction code
 */
u8 LCD_CMD_HOME();

/**
 * @brief Returns the entry mode set instruction code
 *
 * @param increment Increments the DDRAM address by one when set to `1` or decrements the address by one when set to `0`
 * @param shift Shifts the display when set to `1` (stationary cursor illusion), and doesn't shift when set to `0`
 */
u8 LCD_CMD_ENTRY_MODE(bool increment, bool shift);

/**
 * @brief Returns the display control instruction code
 *
 * @param state Specifies whether the display is on `1` or off `0`
 * @param cursor Specifies whether the cursor is displayed `1` or not `0`
 * @param blink Specifies whether the cursor blinks `1` or not `0`
 */
u8 LCD_CMD_DISPLAY(bool state, bool cursor, bool blink);

/**
 * @brief Returns the shift instruction code
 *
 * @param mode Shift the whole screen `1` or the cursor `0`
 * @param direction Shift to the left `1` or to the right `0`
 */
u8 LCD_CMD_SHIFT(bool mode, bool direction);

/**
 * @brief Returns the function set instruction code
 *
 * @param mode Either 8-bit mode `1` or 4-bit mode `0`
 * @param lines Either 2 lines `1` or 1 line `0`
 * @param font Either 5*7 font `1` or 5*10 `0`
 */
u8 LCD_CMD_FUNCTION_SET(bool mode, bool lines, bool font);

/*==========================================
FUNCTION PROTOTYPES
==========================================*/

/**
 * @brief Send the enable signal by lowering the volatage from HIGH -> LOW, then resets it to HIGH again for the next
 * execution.
 */
void LCD_Enable();

/**
 * @brief Executes a command
 *
 * @param command A command code returned by one of the LCD_CMD_* functions
 */
void LCD_Command(u8 command);

/**
 * @brief Sends data to be written to the DDRAM
 *
 * @param data Any 1 byte data that will be stored in the DDRAM
 */
void LCD_Data(u8 data);

/**
 * @brief Executes the clear screen instruction
 */
void LCD_Clear();

/**
 * @brief Initializes the microcontroller's ports/pins to interface with the LCD, then starts the LCD's 8-bit
 * initialization sequence
 */
void LCD_Init();

/**
 * @brief Moves the cursor within the DDRAM
 *
 * @param row The row which the cursor will be moved (zero-indexed)
 * @param column The column which the cursor will be moved (zero-indexed)
 */
void LCD_MoveCursor(u8 row, u8 column);

/**
 * @brief Sends a string to be written to the DDRAM
 *
 * @param string A pointer that points to the first character in the string.
 */
void LCD_SendString(char *string);

/**
 * @brief Sends a string to be written to the screen with wrap
 *
 * @param string A pointer that points to the first character in the string.
 * @param row Specifies which row the string starts to be written.
 * @param column Specifies which column the string starts to be written.
 */
void LCD_SendStringWrap(char *string, u8 row, u8 column);

/**
 * @brief Scrolls the display right or left
 *
 * @param number Number of shifts
 * @param direction Shift to the left `1` or to the right `0`
 */
void LCD_Scroll(u8 number, bool direction);

// I know we didn't study them, but I'll do them anyways.
// Just not now cuz I have no time :)
/*
void LCD_SET_CGRAM(u8 address);
void LCD_STORE_CUST_CHAR(u8 *arr_char, u8 no);
void LCD_PRINT_CUST_CHAR(u8 address, u8 x, u8 y);
void create_custome(u8 *Str, u8 custom_number);
void show_custome(u8 custom_number);
*/

#endif /* LCD_H_ */