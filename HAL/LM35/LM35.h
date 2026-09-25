/*==========================================
  LM35.h
  Temperature Sensor Driver
============================================
  Type           : Driver Header
  Author         : Omar Ezzeldin
==========================================*/

#ifndef LM35_H_
#define LM35_H_

#include "LIB/STD_TYPES.h"
#include "MCAL/ADC.h"

/*==========================================
LM35 CONFIGURATION
==========================================*/

#define LM35_CHANNEL ADC_CHANNEL1
#define LM35_VOLTAGE_PER_DEGREE_mv 10

/*==========================================
FUNCTION PROTOTYPES
==========================================*/

/**
 * @brief Initializes the LM35 input and ADC.
 */
void LM35_Init();

/**
 * @brief Reads the raw ADC result from the LM35.
 *
 * @return Raw 10-bit ADC result.
 */
u16 LM35_Read();

/**
 * @brief Converts an ADC result to millivolts.
 *
 * @param value Raw ADC result.
 *
 * @return Measured input voltage in millivolts.
 */
u16 LM35_GetVoltage(u16 value);

/**
 * @brief Converts a raw ADC result to degrees Celsius.
 *
 * @param value Raw ADC result.
 *
 * @return Temperature in degrees Celsius.
 */
u8 LM35_GetTemperature(u16 value);

#endif /* LM35_H_ */
