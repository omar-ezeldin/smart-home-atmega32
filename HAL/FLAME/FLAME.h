/*==========================================
  FLAME.h
  Flame Sensor Driver
============================================
  Type           : Driver Header
  Author         : Omar Ezzeldin
==========================================*/

#ifndef FLAME_H_
#define FLAME_H_

#include "LIB/STD_TYPES.h"
#include "MCAL/DIO.h"
#include "MCAL/EXTI.h"

/*==========================================
FLAME SENSOR CONFIGURATION
==========================================*/

#define FLAME_SENSOR_PORT PD
#define FLAME_SENSOR_PIN  P2

/*==========================================
FUNCTION PROTOTYPES
==========================================*/

/**
 * @brief Initializes the flame sensor and INT0.
 */
void FLAME_Init();

/**
 * @brief Sets the flame detection callback.
 *
 * @param callbackFunctionPointer Function called when the flame state changes.
 */
void FLAME_SetCallback(void (*callbackFunctionPointer)(void));

/**
 * @brief Gets the current flame detection state.
 *
 * @return `HIGH` when flame is detected, otherwise `LOW`.
 */
u8 FLAME_IsDetected();

#endif /* FLAME_H_ */
