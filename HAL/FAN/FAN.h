/*==========================================
  FAN.h
  Fan Driver
============================================
  Type           : Driver Header
  Author         : Omar Ezzeldin
==========================================*/

#ifndef FAN_H_
#define FAN_H_

#include "LIB/STD_TYPES.h"
#include "MCAL/DIO.h"

/*==========================================
FAN CONFIGURATION
==========================================*/

#define FAN_IN1_PORT PB
#define FAN_IN1_PIN  P0

#define FAN_IN2_PORT PB
#define FAN_IN2_PIN  P1

#define FAN_ENABLE_PORT PB
#define FAN_ENABLE_PIN  P3

#define FAN_TEMPERATURE_THRESHOLD 25
#define FAN_TEMPERATURE_SPEED_50  30
#define FAN_TEMPERATURE_SPEED_75  35
#define FAN_TEMPERATURE_SPEED_100 40

#define FAN_SPEED_25  64
#define FAN_SPEED_50  128
#define FAN_SPEED_75  191
#define FAN_SPEED_100 255

/*==========================================
FUNCTION PROTOTYPES
==========================================*/

/**
 * @brief Initializes the fan control pins.
 */
void FAN_Init();

/**
 * @brief Updates the fan state according to the temperature.
 *
 * @param temperature Temperature in degrees Celsius.
 */
void FAN_Update(u8 temperature);

/**
 * @brief Gets the current fan state.
 *
 * @return `HIGH` when the fan is enabled, otherwise `LOW`.
 */
u8 FAN_IsOn();

#endif /* FAN_H_ */
