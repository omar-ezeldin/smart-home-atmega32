/*==========================================
  FLAME.c
  Flame Sensor Driver
============================================
  Type           : Driver Implementation
  Author         : Omar Ezzeldin
==========================================*/

#ifndef FLAME_C_
#define FLAME_C_

#include "HAL/FLAME/FLAME.h"

static volatile u8 flameDetected = LOW;

static void FLAME_UpdateState() {
    flameDetected = DIO_GetPinValue(FLAME_SENSOR_PORT, FLAME_SENSOR_PIN);
    DIO_SetPinValue(FLAME_BUZZER_PORT, FLAME_BUZZER_PIN, flameDetected);
}

void FLAME_Init() {
    DIO_SetPinDirection(FLAME_SENSOR_PORT, FLAME_SENSOR_PIN, INPUT);
    DIO_SetPinDirection(FLAME_BUZZER_PORT, FLAME_BUZZER_PIN, OUTPUT);
    DIO_SetPinValue(FLAME_BUZZER_PORT, FLAME_BUZZER_PIN, LOW);
    FLAME_UpdateState();

    EXTI_SetCallBack(EXT_INT0, FLAME_UpdateState);
    EXTI_SetTrigger(EXT_INT0, LOGICAL_CHANGE);
    EXTI_EnableInterrupt(EXT_INT0);
    EXTI_EnableGlobal();
}

u8 FLAME_IsDetected() {
    return flameDetected;
}

#endif /* FLAME_C_ */
