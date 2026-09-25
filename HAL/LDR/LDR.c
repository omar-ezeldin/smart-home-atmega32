/*==========================================
  LDR.c
  Light Dependent Resistor Driver
============================================
  Type           : Driver Implementation
  Author         : Omar Ezzeldin
==========================================*/

#ifndef LDR_C_
#define LDR_C_

#include "HAL/LDR/LDR.h"
#include "MCAL/DIO.h"

const u16 LDR_CALIBRATION_VOLTAGES_mv[LDR_CALIBRATION_POINTS] = {
    5, 25, 50, 98, 238, 455, 833, 1667, 2500, 3333};

const u16 LDR_CALIBRATION_INTENSITIES_x100[LDR_CALIBRATION_POINTS] = {
    0, 1111, 2222, 3333, 4444, 5556, 6667, 7778, 8889, 10000};

void LDR_Init() {
    DIO_SetPinDirection(PA, P0, INPUT);
    ADC_Init();
}

u16 LDR_Read() {
    return ADC_Read(LDR_CHANNEL);
}

u16 LDR_GetVoltage(u16 value) {
    return (u16)(((u32)value * ADC_VOLTAGE_REF_mv) / (ADC_MAX_NO_OF_STEPS - 1));
}

u8 LDR_GetIntensity(u16 value) {
    u16 voltage = LDR_GetVoltage(value);
    u8 index;

    if (voltage <= LDR_CALIBRATION_VOLTAGES_mv[0]) {
        return 0;
    }

    if (voltage >= LDR_CALIBRATION_VOLTAGES_mv[LDR_CALIBRATION_POINTS - 1]) {
        return 100;
    }

    for (index = 0; index < LDR_CALIBRATION_POINTS - 1; index++) {
        if (voltage <= LDR_CALIBRATION_VOLTAGES_mv[index + 1]) {
            u16 voltageRange = LDR_CALIBRATION_VOLTAGES_mv[index + 1] -
                               LDR_CALIBRATION_VOLTAGES_mv[index];
            u16 intensityRange =
                LDR_CALIBRATION_INTENSITIES_x100[index + 1] -
                LDR_CALIBRATION_INTENSITIES_x100[index];
            u16 intensity =
                LDR_CALIBRATION_INTENSITIES_x100[index] +
                (((u32)(voltage - LDR_CALIBRATION_VOLTAGES_mv[index]) *
                  intensityRange) /
                 voltageRange);

            return (u8)((intensity + 50) / 100);
        }
    }

    return 100;
}

#endif /* LDR_C_ */
