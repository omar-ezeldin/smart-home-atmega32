/*==========================================
  SEVSEG.h
  7 Segment Driver
============================================
  Type           : Driver Header
  Author         : Omar Ezzeldin
==========================================*/

#ifndef SEVSEG_H_
#define SEVSEG_H_

#include "LIB/STD_TYPES.h"

/**
 * @brief Writes a number to the 7 segment.
 *
 * @param port the port of the 7 segment
 * @param number The number to display from 0 to 9;
 * @param type The type of the 7 segment `1` for common ground and `0` for common anode;
 */
void SEVSEG_Write(u8 port, u8 number, bool type);

/**
 * @brief Clears the 7 segment
 *
 * @param port the port of the 7 segment
 * @param type The type of the 7 segment `1` for common ground and `0` for common anode;
 */
void SEVSEG_Clear(u8 port, bool type);

#endif /* SEVSEG_H_ */