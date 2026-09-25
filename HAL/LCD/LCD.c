/*==========================================
  LCD.h
  LCD Driver
============================================
  Type           : Driver Implementation
  Author         : Omar Ezzeldin
==========================================*/

#ifndef LCD_C_
#define LCD_C_

#include "HAL/LCD.h"
#include "MCAL/DIO.h"
#include <util/delay.h>

/*==========================================
COMMANDS DEFINITIONS
==========================================*/

u8 LCD_CMD_CLR() {
    // Looks redundant and could be done with a #define at the top
    // but I want to unify the commands structure in the driver :)
    return 1;
}

u8 LCD_CMD_HOME() {
    // Looks redundant and could be done with a #define at the top
    // but I want to unify the commands structure in the driver :)
    return 2;
}

u8 LCD_CMD_ENTRY_MODE(bool increment, bool shift) {
    u8 instruction = 1 << 2;
    instruction |= (increment << 1);
    instruction |= (shift);
    return instruction;
}

u8 LCD_CMD_DISPLAY(bool state, bool cursor, bool blink) {
    u8 instruction = 1 << 3;
    instruction |= (state << 2);
    instruction |= (cursor << 1);
    instruction |= (blink);
    return instruction;
}

u8 LCD_CMD_SHIFT(bool mode, bool direction) {
    u8 instruction = 1 << 4;
    instruction |= (mode << 3);
    instruction |= (direction << 2);
    return instruction;
}

u8 LCD_CMD_FUNCTION_SET(bool mode, bool lines, bool font) {
    u8 instruction = 1 << 5;
    instruction |= (mode << 4);
    instruction |= (lines << 3);
    instruction |= (font << 2);
    return instruction;
}

/*==========================================
DRIVER FUNCTION DEFINITIONS
==========================================*/

void LCD_Enable() {
    DIO_SetPinValue(LCD_CONTROL_PORT, LCD_E, LOW);
    DIO_SetPinValue(LCD_CONTROL_PORT, LCD_E, HIGH);
}

void LCD_Command(u8 command) {
    DIO_SetPinValue(LCD_CONTROL_PORT, LCD_RS, LOW);
    DIO_SetPortValue(LCD_DATA_PORT, command);
    LCD_Enable();

    if (command == LCD_CMD_CLR() || command == LCD_CMD_HOME()) {
        _delay_ms(2);
    } else {
        _delay_us(50);
    }
}

void LCD_Data(u8 data) {
    DIO_SetPinValue(LCD_CONTROL_PORT, LCD_RS, HIGH);
    DIO_SetPortValue(LCD_DATA_PORT, data);
    LCD_Enable();
    _delay_us(50);
}

void LCD_Clear() {
    LCD_Command(LCD_CMD_CLR());
}

void LCD_Init() {
    _delay_ms(35);
    // Ports/Pins Initialization
    DIO_SetPinDirection(LCD_CONTROL_PORT, LCD_RS, OUTPUT);
    DIO_SetPinDirection(LCD_CONTROL_PORT, LCD_E, OUTPUT);
    DIO_SetPinValue(LCD_CONTROL_PORT, LCD_E, HIGH);
    DIO_SetPortDirection(LCD_DATA_PORT, PORT_OUTPUT);

    // LCD initialization
    LCD_Command(LCD_CMD_FUNCTION_SET(1, 1, 1));
    LCD_Command(LCD_CMD_DISPLAY(1, 0, 0));
    LCD_Clear();
    LCD_Command(LCD_CMD_ENTRY_MODE(1, 0));
}

void LCD_SendString(char *string) {
    while (*string != '\0') {
        LCD_Data(*string);
        string++;
    }
}

void LCD_MoveCursor(u8 row, u8 column) {
    if (row >= 2 || column >= 16) return;

    LCD_Command(0x80 | (0x40 * row + column));
}

void LCD_SendStringWrap(char *string, u8 row, u8 column) {
    if (row >= 2 || column >= 16) return;

    while (*string != '\0') {
        if (column == 16) {
            row    = row ? 0 : 1;
            column = 0;
        }
        LCD_MoveCursor(row, column);
        LCD_Data(*string);
        string++;
        column++;
    }
}

void LCD_Scroll(u8 number, bool direction) {
    while (number--) {
        LCD_Command(LCD_CMD_SHIFT(1, direction));
    }
}

#endif /* LCD_C_ */