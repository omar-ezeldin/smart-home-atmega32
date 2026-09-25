/*==========================================
  LM35.c
  Temperature Sensor Driver
============================================
  Type           : Driver Implementation
  Author         : Omar Ezzeldin
==========================================*/

#ifndef LM35_C_
#define LM35_C_

#include "HAL/LM35/LM35.h"
#include "MCAL/DIO.h"

void LM35_Init() {
    DIO_SetPinDirection(PA, P1, INPUT);
    ADC_Init();
}

u16 LM35_Read() {
    return ADC_Read(LM35_CHANNEL);
}

u16 LM35_GetVoltage(u16 value) {
    return (u16)(((u32)value * ADC_VOLTAGE_REF_mv) / (ADC_MAX_NO_OF_STEPS - 1));
}

u8 LM35_GetTemperature(u16 value) {
    return (u8)(LM35_GetVoltage(value) / LM35_VOLTAGE_PER_DEGREE_mv);
}

#endif /* LM35_C_ */
