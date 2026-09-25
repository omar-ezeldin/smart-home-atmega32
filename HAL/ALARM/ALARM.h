/*==========================================
  ALARM.h
  Alarm Driver
============================================
  Type           : Driver Header
  Author         : Omar Ezzeldin
==========================================*/

#ifndef ALARM_H_
#define ALARM_H_

#include "LIB/STD_TYPES.h"
#include "MCAL/DIO.h"

/*==========================================
ALARM CONFIGURATION
==========================================*/

#define ALARM_PORT PD
#define ALARM_PIN  P3

/*==========================================
FUNCTION PROTOTYPES
==========================================*/

/**
 * @brief Initializes the alarm output.
 */
void ALARM_Init();

/**
 * @brief Sets the alarm output state.
 *
 * @param state Alarm output state.
 */
void ALARM_SetState(u8 state);

#endif /* ALARM_H_ */
