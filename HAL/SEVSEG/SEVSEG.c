/*==========================================
  SEVSEG.h
  7 Segment Driver
============================================
  Type           : Driver Implementation
  Author         : Omar Ezzeldin
==========================================*/

#ifndef SEVSEG_C_
#define SEVSEG_C_

#include "HAL/SEVSEG.h"
#include "LIB/STD_TYPES.h"
#include "MCAL/DIO.h"

u8 number_segments[10] = {0b00111111, 0b00000110, 0b01011011, 0b01001111, 0b01100110,
                          0b01101101, 0b01111101, 0b00000111, 0b01111111, 0b01101111};

void SEVSEG_Write(u8 port, u8 number, bool type) {
    DIO_SetPortDirection(port, PORT_OUTPUT);
    if (type == 1) {
        DIO_SetPortValue(port, number_segments[number]);
    } else {
        DIO_SetPortValue(port, ~number_segments[number]);
    }
}

void SEVSEG_Clear(u8 port, bool type) {
    DIO_SetPortDirection(port, PORT_OUTPUT);
    if (type == 1) {
        DIO_SetPortValue(port, PORT_LOW);
    } else {
        DIO_SetPortValue(port, PORT_HIGH);
    }
}

#endif /* SEVSEG_C_ */