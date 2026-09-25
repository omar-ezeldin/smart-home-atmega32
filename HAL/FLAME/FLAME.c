/*==========================================
  FLAME.c
  Flame Sensor Driver
============================================
  Type           : Driver Implementation
  Author         : Omar Ezzeldin
==========================================*/

#ifndef FLAME_C_
#define FLAME_C_

#include "HAL/FLAME.h"

static volatile u8 flameDetected = LOW;
static void (*FLAME_Callback)(void) = NULL_PTR;

static void FLAME_UpdateState() {
    flameDetected = DIO_GetPinValue(FLAME_SENSOR_PORT, FLAME_SENSOR_PIN);

    if (FLAME_Callback != NULL_PTR) {
        FLAME_Callback();
    }
}

void FLAME_Init() {
    DIO_SetPinDirection(FLAME_SENSOR_PORT, FLAME_SENSOR_PIN, INPUT);

    EXTI_SetCallBack(EXT_INT0, FLAME_UpdateState);
    EXTI_SetTrigger(EXT_INT0, LOGICAL_CHANGE);
    EXTI_EnableInterrupt(EXT_INT0);
    EXTI_EnableGlobal();
    FLAME_UpdateState();
}

void FLAME_SetCallback(void (*callbackFunctionPointer)(void)) {
    FLAME_Callback = callbackFunctionPointer;
}

u8 FLAME_IsDetected() {
    return flameDetected;
}

#endif /* FLAME_C_ */
