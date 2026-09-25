/*==========================================
  LDR.h
  Light Dependent Resistor Driver
============================================
  Type           : Driver Header
  Author         : Omar Ezzeldin
==========================================*/

#ifndef LDR_H_
#define LDR_H_

#include "LIB/STD_TYPES.h"
#include "MCAL/ADC.h"

/*==========================================
LDR CONFIGURATION
==========================================*/

#define LDR_CHANNEL ADC_CHANNEL0

#define LDR_CALIBRATION_POINTS 10

/*==========================================
FUNCTION PROTOTYPES
==========================================*/

/**
 * @brief Initializes the LDR input and ADC.
 */
void LDR_Init();

/**
 * @brief Reads the raw ADC result from the LDR.
 *
 * @return Raw 10-bit ADC result.
 */
u16 LDR_Read();

/**
 * @brief Converts an ADC result to millivolts.
 *
 * @param value Raw ADC result.
 *
 * @return Measured input voltage in millivolts.
 */
u16 LDR_GetVoltage(u16 value);

/**
 * @brief Converts a raw ADC result to calibrated light intensity.
 *
 * @return Calibrated light intensity percentage.
 */
u8 LDR_GetIntensity();

#endif /* LDR_H_ */
