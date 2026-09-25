/*==========================================
  LED.h
  LED Driver
============================================
  Type           : Driver Header
  Author         : Omar Ezzeldin
==========================================*/

#ifndef LED_H_
#define LED_H_

#include "LIB/STD_TYPES.h"
#include "MCAL/DIO.h"

/*==========================================
LED CONFIGURATION
==========================================*/

#define RED_LED_PORT   PB
#define RED_LED_PIN    P5
#define GREEN_LED_PORT PB
#define GREEN_LED_PIN  P6
#define BLUE_LED_PORT  PB
#define BLUE_LED_PIN   P7

#define LED_INTENSITY_THRESHOLD_15 15
#define LED_INTENSITY_THRESHOLD_50 50
#define LED_INTENSITY_THRESHOLD_70 70

/*==========================================
FUNCTION PROTOTYPES
==========================================*/

/**
 * @brief Initializes the LED pins.
 */
void LED_Init();

/**
 * @brief Updates the LEDs according to the light intensity.
 *
 * @param intensity Light intensity percentage.
 */
void LED_Update(u8 intensity);

#endif /* LED_H_ */
