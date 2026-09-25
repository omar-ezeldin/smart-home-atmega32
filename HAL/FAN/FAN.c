/*==========================================
  FAN.c
  Fan Driver
============================================
  Type           : Driver Implementation
  Author         : Omar Ezzeldin
==========================================*/

#ifndef FAN_C_
#define FAN_C_

#include "HAL/FAN.h"
#include "MCAL/TIMER.h"

static u8 fanOn = LOW;

void FAN_Init() {
    DIO_SetPinDirection(FAN_IN1_PORT, FAN_IN1_PIN, OUTPUT);
    DIO_SetPinDirection(FAN_IN2_PORT, FAN_IN2_PIN, OUTPUT);
    DIO_SetPinDirection(FAN_ENABLE_PORT, FAN_ENABLE_PIN, OUTPUT);

    DIO_SetPinValue(FAN_IN1_PORT, FAN_IN1_PIN, LOW);
    DIO_SetPinValue(FAN_IN2_PORT, FAN_IN2_PIN, LOW);
    DIO_SetPinValue(FAN_ENABLE_PORT, FAN_ENABLE_PIN, LOW);

    TIMER0_Init();
}

void FAN_Update(u8 temperature) {
    if (temperature < FAN_TEMPERATURE_THRESHOLD) {
        DIO_SetPinValue(FAN_IN1_PORT, FAN_IN1_PIN, LOW);
        DIO_SetPinValue(FAN_IN2_PORT, FAN_IN2_PIN, LOW);
        TIMER0_SetOutputCompareValue(0);
        TIMER0_Start();
        fanOn = LOW;
    } else {
        DIO_SetPinValue(FAN_IN1_PORT, FAN_IN1_PIN, HIGH);
        DIO_SetPinValue(FAN_IN2_PORT, FAN_IN2_PIN, LOW);

        if (temperature >= FAN_TEMPERATURE_SPEED_100) {
            TIMER0_SetOutputCompareValue(FAN_SPEED_100);
        } else if (temperature >= FAN_TEMPERATURE_SPEED_75) {
            TIMER0_SetOutputCompareValue(FAN_SPEED_75);
        } else if (temperature >= FAN_TEMPERATURE_SPEED_50) {
            TIMER0_SetOutputCompareValue(FAN_SPEED_50);
        } else {
            TIMER0_SetOutputCompareValue(FAN_SPEED_25);
        }

        TIMER0_Start();
        fanOn = HIGH;
    }
}

u8 FAN_IsOn() {
    return fanOn;
}

#endif /* FAN_C_ */
