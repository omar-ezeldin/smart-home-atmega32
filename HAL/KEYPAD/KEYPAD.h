/*==========================================
  KEYPAD.h
  Keypad Driver
============================================
  Type           : Driver Header
  Author         : Omar Ezzeldin
==========================================*/

#ifndef KEYPAD_H_
#define KEYPAD_H_

#include "LIB/STD_TYPES.h"
#include "MCAL/DIO.h"

#define KP_NROW 4
#define KP_NCOL 4

#define KP_PORT PA

#define KP_R1 P7
#define KP_R2 P6
#define KP_R3 P5
#define KP_R4 P4
#define KP_C1 P3
#define KP_C2 P2
#define KP_C3 P1
#define KP_C4 P0

/**
 * @brief Initializes the keypad ports/pins
 */
void KP_Init();

/**
 * @brief Returns the pressed button character
 */
char KP_GetKeyPressed();

#endif /* KEYPAD_H_ */