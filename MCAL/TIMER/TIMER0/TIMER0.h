/*==========================================
  TIMER0.h
  Timer 0 Driver
============================================
  Type           : Driver Header
  Author         : Omar Ezzeldin
==========================================*/

#ifndef TIMER0_H_
#define TIMER0_H_

#include "LIB/STD_TYPES.h"
#include "MCAL/TIMER.h"

/*==========================================
TIMER 0 REGISTER DEFINITIONS
==========================================*/

#define TCCR0 (*((volatile u8 *)0x53)) // Timer/Counter Control Register
#define TCNT0 (*((volatile u8 *)0x52)) // Timer/Counter Register
#define OCR0  (*((volatile u8 *)0x5C)) // Output Compare Register

/*==========================================
TCCR0 CONFIGURATION BITS
==========================================*/

#define FOC0  7 // Force Output Compare Bit - Responsible for forcing a compare
#define WGM00 6 // Waveform Generation Mode Bit 0 - Responsible for configuring the timer's mode
#define COM01 5 // Compare Output Mode Bit 1 - Responsible for different options depending on the timer's mode
#define COM00 4 // Compare Output Mode Bit 0 - Responsible for different options depending on the timer's mode
#define WGM01 3 // Waveform Generation Mode Bit 1 - Responsible for configuring the timer's mode
#define CS02  2 // Clock Select Bit 2 - Resposible for setting the prescaler
#define CS01  1 // Clock Select Bit 1 - Resposible for setting the prescaler
#define CS00  0 // Clock Select Bit 0 - Resposible for setting the prescaler

/*==========================================
TIMSK CONFIGURATION BITS (TIMER 0)
==========================================*/

#define TOIE0 0 // Timer/Counter0 Overflow Interrupt Enable
#define OCIE0 1 // Timer/Counter0 Output Compare Match Interrupt Enable

/*==========================================
TIMER 0 SOFTWARE CONFIGURATION
==========================================*/

#define TIMER0_MODE       TIMER_MD_FASTPWM
#define TIMER0_PRESCALER  TIMER_PS_64

#define TIMER0_OUTPUT_DISCONNECTED  0
#define TIMER0_OUTPUT_TOGGLE        1
#define TIMER0_OUTPUT_NON_INVERTING 2
#define TIMER0_OUTPUT_INVERTING     3

#define TIMER0_OUTPUT_MODE TIMER0_OUTPUT_NON_INVERTING

/*==========================================
FUNCTION PROTOTYPES
==========================================*/

/**
 * @brief Initializes Timer 0
 *
 */
void TIMER0_Init();

/**
 * @brief Starts Timer 0
 */
void TIMER0_Start();

/**
 * @brief Stops Timer 0
 */
void TIMER0_Stop();

/**
 * @brief Sets the Timer 0 output compare value.
 *
 * @param value The output compare value.
 */
void TIMER0_SetOutputCompareValue(u8 value);

/**
 * @brief Enables Interrupts for Timer 0
 */
void TIMER0_EnableInterrupt();

/**
 * @brief Disables Interrupts for Timer 0
 */
void TIMER0_DisableInterrupt();

/**
 * @brief Returns the real prescaler value instead of the macro.
 */
u32 TIMER0_GetRealPrescaler();

/**
 * @brief Sets time on the timer.
 *
 * @param time The time to set in milliseconds.
 */
void TIMER0_SetTime(u32 time);

/**
 * @brief Sets the timer's callback
 *
 * @param callbackFunctionPointer The timer's callback function pointer
 */
void TIMER0_SetCallback(void (*callbackFunctionPointer)(void));

#endif /* TIMER0_H_ */