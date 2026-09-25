/*==========================================
  DIO.h
  Digital Input/Output Driver
============================================
  Type           : Driver Header
  Author         : Omar Ezzeldin
==========================================*/

#ifndef DIO_H_
#define DIO_H_

#include "LIB/BIT_MATH.h"
#include "LIB/STD_TYPES.h"

/*==========================================
PORT REGISTERS
==========================================*/

#define PORTA *((volatile u8 *)0x3B) // Port A Data Register
#define DDRA  *((volatile u8 *)0x3A) // Port A Data Direction Register
#define PINA  *((volatile u8 *)0x39) // Port A Input Pins Register

#define PORTB *((volatile u8 *)0x38) // Port B Data Register
#define DDRB  *((volatile u8 *)0X37) // Port B Data Direction Register
#define PINB  *((volatile u8 *)0X36) // Port B Input Pins Register

#define PORTC *((volatile u8 *)0x35) // Port C Data Register
#define DDRC  *((volatile u8 *)0x34) // Port C Data Direction Register
#define PINC  *((volatile u8 *)0x33) // Port C Input Pins Register

#define PORTD *((volatile u8 *)0x32) // Port D Data Register
#define DDRD  *((volatile u8 *)0x31) // Port D Data Direction Register
#define PIND  *((volatile u8 *)0x30) // Port D Input Pins Register

/*==========================================
PORT/PIN DEFINITIONS
==========================================*/

#define N_PORTS 4 // Max number of ports in the MCU
#define N_PINS  8 // Max number of pins per port in the MCU

#define PA 0 // ID of Port A
#define PB 1 // ID of Port B
#define PC 2 // ID of Port C
#define PD 3 // ID of Port D

#define P0 0 // ID of Pin 0
#define P1 1 // ID of Pin 1
#define P2 2 // ID of Pin 2
#define P3 3 // ID of Pin 3
#define P4 4 // ID of Pin 4
#define P5 5 // ID of Pin 5
#define P6 6 // ID of Pin 6
#define P7 7 // ID of Pin 7

/*==========================================
LOGIC/DIRECTION DEFINITIONS
==========================================*/

#define LOW  0
#define HIGH 1

#define INPUT  0
#define OUTPUT 1

#define PORT_LOW  0
#define PORT_HIGH 0xFF

#define PORT_INPUT  0
#define PORT_OUTPUT 0xFF

/*==========================================
PORT FUNCTION PROTOTYPES
==========================================*/

/**
 * @brief Sets the direction of all pins in a port.
 *
 * @param PORT_ID   ID of the target port.
 * @param DIRECTION Port direction configuration.
 */
void DIO_SetPortDirection(u8 PORT_ID, u8 DIRECTION);

/**
 * @brief Sets the logic level of all pins in a port.
 *
 * @param PORT_ID ID of the target port.
 * @param VALUE   Value to write to the port.
 */
void DIO_SetPortValue(u8 PORT_ID, u8 VALUE);

/**
 * @brief Reads the current logic levels of all pins in a port.
 *
 * @param PORT_ID ID of the target port.
 *
 * @return Current value of the port.
 */
u8 DIO_GetPortValue(u8 PORT_ID);

/*==========================================
PIN FUNCTION PROTOTYPES
==========================================*/

/**
 * @brief Sets the direction of a specific pin.
 *
 * @param PORT_ID   Target port ID
 * @param PIN       Target pin number
 * @param DIRECTION Pin direction
 */
void DIO_SetPinDirection(u8 PORT_ID, u8 PIN, u8 DIRECTION);

/**
 * @brief Sets the logic level of a specific pin.
 *
 * @param PORT_ID Target port ID
 * @param PIN     Target pin number
 * @param VALUE   Pin logic level (LOW or HIGH)
 */
void DIO_SetPinValue(u8 PORT_ID, u8 PIN, u8 VALUE);

/**
 * @brief Reads the current logic level of a specific pin
 *
 * @param PORT_ID Target port ID
 * @param PIN     Target pin number
 *
 * @return Current logic level of the pin
 */
u8 DIO_GetPinValue(u8 PORT_ID, u8 PIN);

/**
 * @brief Toggles the logic level of a specific pin
 *
 * @param PORT_ID Target port ID
 * @param PIN     Target pin number
 */
void DIO_TogglePinValue(u8 PORT_ID, u8 PIN);

#endif /* DIO_H_ */