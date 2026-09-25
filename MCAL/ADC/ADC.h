/*==========================================
  ADC.c
  Analog to Digital Converter
============================================
  Type           : Driver Header
  Author         : Omar Ezzeldin
==========================================*/

#ifndef ADC_H_
#define ADC_H_

#include "LIB/STD_TYPES.h"

/*==========================================
ADC REGISTERS
==========================================*/

#define ADMUX  (*((volatile u8 *)0x27))  // ADC Multiplexer Selection Register
#define ADCSRA (*((volatile u8 *)0x26))  // ADC Control and Status Register
#define ADCH   (*((volatile u8 *)0x25))  // ADC Data Register High Byte
#define ADCL   (*((volatile u8 *)0x24))  // ADC Data Register Low Byte
#define ADCLH  (*((volatile u16 *)0x24)) // ADC Data Register (Complete)
#define SFIOR  (*((volatile u8 *)0x50))  // Special FunctionIO Register

/*==========================================
CONFIGURATION BITS
==========================================*/

#define ADMUX_REFS1 7 // Reference Selection Bit 1
#define ADMUX_REFS0 6 // Reference Selection Bit 0
#define ADMUX_ADLAR 5 // ADC Left Adjust Result Bit

#define ADCSRA_ADEN  7 // ADC Enable
#define ADCSRA_ADSC  6 // ADC Start Conversion
#define ADCSRA_ADATE 5 // ADC Auto Trigger Enable
#define ADCSRA_ADIF  4 // ADC Interrupt Flag
#define ADCSRA_ADIE  3 // ADC Interrupt Enable
#define ADCSRA_ADPS2 2 // ADC Prescaler Bit 2
#define ADCSRA_ADPS1 1 // ADC Prescaler Bit 1
#define ADCSRA_ADPS0 0 // ADC Prescaler BIt 0

#define SFIOR_ADTS2 7 // ADC Auto Trigger Source Bit 2
#define SFIOR_ADTS1 6 // ADC Auto Trigger Source Bit 1
#define SFIOR_ADTS0 5 // ADC Auto Trigger Source Bit 0

/*==========================================
LOGIC DEFINITIONS
==========================================*/

#define ADC_DISABLE 0
#define ADC_ENABLE  1

#define INT_DISABLE 0
#define INT_ENABLE  1

#define NULL_PTR 0

/*==========================================
ADC VOLTAGE REFERENCE DEFINITIONS
==========================================*/

#define AREF          0
#define AVCC          1
#define INTERNAL_2_56 3

/*==========================================
ADJUST RESULT DEFINITIONS
==========================================*/

#define ADC_RIGHT_ADJUSTMENT 0
#define ADC_LEFT_ADJUSTMENT  1

/*==========================================
ADC CHANNELS DEFINITIONS
==========================================*/

#define ADC_CHANNEL0 0
#define ADC_CHANNEL1 1
#define ADC_CHANNEL2 2
#define ADC_CHANNEL3 3
#define ADC_CHANNEL4 4
#define ADC_CHANNEL5 5
#define ADC_CHANNEL6 6
#define ADC_CHANNEL7 7

/*==========================================
ADC AUTO TRIGGER DEFINITIONS
==========================================*/

#define ADC_SINGLE_CONVERSION  0
#define ADC_FREE_RUNNING       1
#define ADC_ANALOG_COMPARATOR  2
#define ADC_EXTI0              3
#define ADC_TIM0_CTC           4
#define ADC_TIM0_OVF           5
#define ADC_TIM1_CTC_CHANNEL_B 6
#define ADC_TIM1_OVF           7
#define ADC_TIM1_ICU           8

/*==========================================
ADC PRESCALER DEFINITIONS
==========================================*/

#define ADC_PRE_2   0
#define ADC_PRE_4   2
#define ADC_PRE_8   3
#define ADC_PRE_16  4
#define ADC_PRE_32  5
#define ADC_PRE_64  6
#define ADC_PRE_128 7

/*==========================================
GENERAL CONFIGURATION
==========================================*/

/**
 * @brief ADC Status Configuration.
 *
 * @note Could be set to `ADC_ENABLE` or `ADC_DISABLE`
 */
#define ADC_STATUS ADC_ENABLE

/**
 * @brief ADC Interrupt Status
 *
 * @note Could be set to `INT_ENABLE` or `INT_DISABLE`
 */
#define INT_STATUS INT_DISABLE

/**
 * @brief ADC Reference Voltage
 *
 * @note Could be set to `AREF`, `AVCC` or `INTERNAL_2_56`
 */
#define ADC_VREF AVCC

/**
 * @brief ADC Adjustment
 *
 * @note Could be set to `ADC_RIGHT_ADJUSTMENT` or `ADC_LEFT_ADJUSTMENT`
 */
#define ADC_ADJUSTMENT ADC_RIGHT_ADJUSTMENT

/**
 * @brief ADC Channel
 *
 * @note Could be set to `ADC_CHANNEL0` till `ADC_CHANNEL7`
 */
#define ADC_CHANNEL ADC_CHANNEL0

/**
 * @brief ADC Auto-triggering Source
 *
 * @note
 * Could be set to `ADC_SINGLE_CONVERSION`, `ADC_FREE_RUNNING`, `ADC_ANALOG_COMPARATOR`,`ADC_EXTI0`,`ADC_TIM0_CTC`,
 * `ADC_TIM0_OVF`, `ADC_TIM1_CTC_CHANNEL_B`,`ADC_TIM1_OVF`,`ADC_TIM1_ICU`
 */
#define ADC_TRIGGERING_SOURCE ADC_SINGLE_CONVERSION

/**
 * @brief ADC Prescaler
 *
 * @note
 * `ADC_PRE_2`, `ADC_PRE_4`, `ADC_PRE_8`, `ADC_PRE_16`, `ADC_PRE_32`, `ADC_PRE_64`, `ADC_PRE_128`.
 */
#define ADC_PRESCALLER ADC_PRE_128

/**
 * @brief Reference Volatage in mV
 */
#define ADC_VOLTAGE_REF_mv 5000

/**
 * @brief ADC number of steps
 */
#define ADC_MAX_NO_OF_STEPS 1024

/*==========================================
FUNCTION PROTOTYPES
==========================================*/

/**
 * @brief Initializes the ADC
 */
void ADC_Init();

/**
 * @brief Start ADC on a given channel
 *
 * @param channel The channel to start converting
 */
void ADC_StartConversion(u8 channel);

/**
 * @brief Gets the conversion result
 */
u16 ADC_GetResult();

/**
 * @brief Reads a complete ADC conversion from a channel.
 *
 * @param channel The channel to read.
 */
u16 ADC_Read(u8 channel);

/**
 * @brief Sets the ADC prescaler
 *
 * @param prescaler The prescaler to set.
 */
void ADC_SetPrescaler(u8 prescaler);

/**
 * @brief Enables the ADC Interrupt
 */
void ADC_EnableInterrupt();

/**
 * @brief Disables the ADC Interrupt
 */
void ADC_DisableInterrupt();

/**
 * @brief Sets the ADC Callback
 *
 * @param callbackFunctionPointer The pointer of the callback function
 */
void ADC_SetCallback(void (*callbackFunctionPointer)(void));

#endif /* ADC_H_ */