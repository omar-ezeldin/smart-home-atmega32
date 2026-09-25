/*==========================================
  ALARM.c
  Alarm Driver
============================================
  Type           : Driver Implementation
  Author         : Omar Ezzeldin
==========================================*/

#ifndef ALARM_C_
#define ALARM_C_

#include "HAL/ALARM.h"

void ALARM_Init() {
    DIO_SetPinDirection(ALARM_PORT, ALARM_PIN, OUTPUT);
    ALARM_SetState(LOW);
}

void ALARM_SetState(u8 state) {
    DIO_SetPinValue(ALARM_PORT, ALARM_PIN, state);
}

#endif /* ALARM_C_ */
