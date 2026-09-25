/*==========================================
  EXTI.h
  External Interrupt Driver
============================================
  Type           : Driver Header
  Author         : Omar Ezzeldin
==========================================*/

#ifndef EXTI_H_
#define EXTI_H_

#include "LIB/STD_TYPES.h"

/*==========================================
REGISTERS
==========================================*/

#define SREG   *((volatile u8 *)0x5F) // Status Register
#define GICR   *((volatile u8 *)0x5B) // General Interrupt Control Register
#define GIFR   *((volatile u8 *)0x5A) // General Interrupt Flag Register
#define MCUCR  *((volatile u8 *)0x55) // MCU Control Register
#define MCUCSR *((volatile u8 *)0x54) // MCU Control and Status Register

/*==========================================
CONFIGURATION BITS
==========================================*/

#define SREG_I    7 // Responsible for enabling/disabling interrupts globally in the Status Register `SREG`
#define GICR_INT0 6 // Responsible for enabling/disabling interrupt 0 in the General Interrupt Control Register `GICR`
#define GICR_INT1 7 // Responsible for enabling/disabling interrupt 1 in the General Interrupt Control Register `GICR`
#define GICR_INT2 5 // Responsible for enabling/disabling interrupt 2 in the General Interrupt Control Register `GICR`

#define GIFR_INT0 6 // Interrupt 0 Flag index in the General Interrupt Flag Register `GIFR`
#define GIFR_INT1 7 // Interrupt 1 Flag index in the General Interrupt Flag Register `GIFR`
#define GIFR_INT2 5 // Interrupt 2 Flag index in the General Interrupt Flag Register `GIFR`

#define MCUCR_ISC00 0 // Interrupt 0 Sense Control Bit
#define MCUCR_ISC01 1 // Interrupt 0 Sense Control Bit
#define MCUCR_ISC10 2 // Interrupt 1 Sense Control Bit
#define MCUCR_ISC11 3 // Interrupt 1 Sense Control Bit
#define MCUCSR_ISC2 6 // Interrupt 2 Sense Control Bit

/*==========================================
SENSE CONTROL DEFINITIONS
==========================================*/

#define LOW_LEVEL      0
#define LOGICAL_CHANGE 1
#define FALLNG_EDGE    2
#define RISING_EDGE    3

/*==========================================
LOGIC DEFINITIONS
==========================================*/

#define NULL_PTR 0
#define ENABLED  1
#define DISABLED 0

/*==========================================
INTERRUPT DEFINITIONS
==========================================*/

#define EXT_INT0 6
#define EXT_INT1 7
#define EXT_INT2 5

/*==========================================
VECTOR DEFINITIONS
==========================================*/

#define _VECTOR(N) __vector_##N

#define INT0_vect         _VECTOR(1)
#define INT1_vect         _VECTOR(2)
#define INT2_vect         _VECTOR(3)
#define TIMER2_COMP_vect  _VECTOR(4)
#define TIMER2_OVF_vect   _VECTOR(5)
#define TIMER1_CAPT_vect  _VECTOR(6)
#define TIMER1_COMPA_vect _VECTOR(7)
#define TIMER1_COMPB_vect _VECTOR(8)
#define TIMER1_OVF_vect   _VECTOR(9)
#define TIMER0_COMP_vect  _VECTOR(10)
#define TIMER0_OVF_vect   _VECTOR(11)
#define SPI_STC_vect      _VECTOR(12)
#define USART_RXC_vect    _VECTOR(13)
#define USART_UDRE_vect   _VECTOR(14)
#define USART_TXC_vect    _VECTOR(15)
#define ADC_vect          _VECTOR(16)
#define EE_RDY_vect       _VECTOR(17)
#define ANA_COMP_vect     _VECTOR(18)
#define TWI_vect          _VECTOR(19)
#define SPM_RDY_vect      _VECTOR(20)

#define ISR(VECT_NO)                                                                                                   \
    void VECT_NO(void) __attribute__((signal));                                                                        \
    void VECT_NO(void)

/*==========================================
ASSEMBLY INSTRUCTION DEFINITIONS
==========================================*/

#define sei() __asm__ __volatile__("sei") // Set Global Interrupt
#define cli() __asm__ __volatile__("cli") // Clear Global Interrupt

/*==========================================
FUNCTION PROTOTYPES
==========================================*/

/**
 * @brief Enables interrupts globally
 */
void EXTI_EnableGlobal();

/**
 * @brief Disables interrupts globally
 */
void EXTI_DisableGlobal();

/**
 * @brief Sets the interrupt trigger (Sense Control)
 *
 * @param interruptNumber The interrupt to configure
 * @param senseControl Can be `LOW_LEVEL`, `LOGICAL_CHANGE`, `FALLNG_EDGE` or `RISING_EDGE`
 *
 * @warning Interrupt 2 only supports `FALLNG_EDGE` or `RISING_EDGE`.
 */
void EXTI_SetTrigger(u8 interruptNumber, u8 senseControl);

/**
 * @brief Disables a specific interrupt
 *
 * @param interruptNumber The interrupt to disable
 */
void EXTI_DisableInterrupt(u8 interruptNumber);

/**
 * @brief Enables a specific interrupt
 *
 * @param interruptNumber The interrupt to enable
 */
void EXTI_EnableInterrupt(u8 interruptNumber);

/**
 * @brief Reads the interrupt flag
 *
 * @param interruptNumber The interrupt to read
 */
u8 EXTI_GetFlag(u8 interruptNumber);

/**
 * @brief Sets the callback function of the interrupt
 *
 * @param interruptNumber Interrupt to configure.
 * @param callbackFunctionPointer Callback function pointer.
 */
void EXTI_SetCallBack(u8 interruptNumber, void (*callbackFunctionPointer)(void));

#endif /* EXTI_H_ */