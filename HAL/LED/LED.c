/*==========================================
  LED.c
  LED Driver
============================================
  Type           : Driver Implementation
  Author         : Omar Ezzeldin
==========================================*/

#ifndef LED_C_
#define LED_C_

#include "HAL/LED/LED.h"

void LED_Init() {
    DIO_SetPinDirection(RED_LED_PORT, RED_LED_PIN, OUTPUT);
    DIO_SetPinDirection(GREEN_LED_PORT, GREEN_LED_PIN, OUTPUT);
    DIO_SetPinDirection(BLUE_LED_PORT, BLUE_LED_PIN, OUTPUT);

    DIO_SetPinValue(RED_LED_PORT, RED_LED_PIN, LOW);
    DIO_SetPinValue(GREEN_LED_PORT, GREEN_LED_PIN, LOW);
    DIO_SetPinValue(BLUE_LED_PORT, BLUE_LED_PIN, LOW);
}

void LED_Update(u8 intensity) {
    if (intensity < LED_INTENSITY_THRESHOLD_15) {
        DIO_SetPinValue(RED_LED_PORT, RED_LED_PIN, HIGH);
        DIO_SetPinValue(GREEN_LED_PORT, GREEN_LED_PIN, HIGH);
        DIO_SetPinValue(BLUE_LED_PORT, BLUE_LED_PIN, HIGH);
    } else if (intensity <= LED_INTENSITY_THRESHOLD_50) {
        DIO_SetPinValue(RED_LED_PORT, RED_LED_PIN, HIGH);
        DIO_SetPinValue(GREEN_LED_PORT, GREEN_LED_PIN, HIGH);
        DIO_SetPinValue(BLUE_LED_PORT, BLUE_LED_PIN, LOW);
    } else if (intensity <= LED_INTENSITY_THRESHOLD_70) {
        DIO_SetPinValue(RED_LED_PORT, RED_LED_PIN, HIGH);
        DIO_SetPinValue(GREEN_LED_PORT, GREEN_LED_PIN, LOW);
        DIO_SetPinValue(BLUE_LED_PORT, BLUE_LED_PIN, LOW);
    } else {
        DIO_SetPinValue(RED_LED_PORT, RED_LED_PIN, LOW);
        DIO_SetPinValue(GREEN_LED_PORT, GREEN_LED_PIN, LOW);
        DIO_SetPinValue(BLUE_LED_PORT, BLUE_LED_PIN, LOW);
    }
}

#endif /* LED_C_ */
