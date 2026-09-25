/*==========================================
  EXTI.c
  External Interrupt Driver
============================================
  Type           : Driver Implementation
  Author         : Omar Ezzeldin
==========================================*/

#include "MCAL/EXTI.h"
#include "LIB/BIT_MATH.h"
#include "LIB/STD_TYPES.h"

void (*EXTI_CallbackPointers[3])(void) = {};

void EXTI_EnableGlobal() {
    // Using the assembly instruction is more efficient
    sei();
    // SET_BIT(SREG, SREG_I); // Alternative
}

void EXTI_DisableGlobal() {
    // Using the assembly instruction is more efficient
    cli();
    // CLR_BIT(SREG, SREG_I); // Alternative
}

void EXTI_SetTrigger(u8 interruptNumber, u8 senseControl) {

    switch (interruptNumber) {
    case EXT_INT0:
        switch (senseControl) {
        case LOW_LEVEL:
            CLR_BIT(MCUCR, MCUCR_ISC00);
            CLR_BIT(MCUCR, MCUCR_ISC01);
            break;
        case LOGICAL_CHANGE:
            SET_BIT(MCUCR, MCUCR_ISC00);
            CLR_BIT(MCUCR, MCUCR_ISC01);
            break;
        case FALLNG_EDGE:
            CLR_BIT(MCUCR, MCUCR_ISC00);
            SET_BIT(MCUCR, MCUCR_ISC01);
            break;
        case RISING_EDGE:
            SET_BIT(MCUCR, MCUCR_ISC00);
            SET_BIT(MCUCR, MCUCR_ISC01);
            break;
        }
        break;
    case EXT_INT1:
        switch (senseControl) {
        case LOW_LEVEL:
            CLR_BIT(MCUCR, MCUCR_ISC10);
            CLR_BIT(MCUCR, MCUCR_ISC11);
            break;
        case LOGICAL_CHANGE:
            SET_BIT(MCUCR, MCUCR_ISC10);
            CLR_BIT(MCUCR, MCUCR_ISC11);
            break;
        case FALLNG_EDGE:
            CLR_BIT(MCUCR, MCUCR_ISC10);
            SET_BIT(MCUCR, MCUCR_ISC11);
            break;
        case RISING_EDGE:
            SET_BIT(MCUCR, MCUCR_ISC10);
            SET_BIT(MCUCR, MCUCR_ISC11);
            break;
        }
        break;
    case EXT_INT2:
        switch (senseControl) {
        case FALLNG_EDGE:
            CLR_BIT(MCUCSR, MCUCSR_ISC2);
            break;
        case RISING_EDGE:
            SET_BIT(MCUCSR, MCUCSR_ISC2);
            break;
        }
        break;
    }
}

void EXTI_DisableInterrupt(u8 interruptNumber) {
    CLR_BIT(GICR, interruptNumber);
}

void EXTI_EnableInterrupt(u8 interruptNumber) {
    SET_BIT(GICR, interruptNumber);
}

u8 EXTI_GetFlag(u8 interruptNumber) {
    return GET_BIT(GIFR, interruptNumber);
}

void EXTI_SetCallBack(u8 interruptNumber, void (*callbackFunctionPointer)(void)) {
    switch (interruptNumber) {
    case EXT_INT0:
        EXTI_CallbackPointers[0] = callbackFunctionPointer;
        break;
    case EXT_INT1:
        EXTI_CallbackPointers[1] = callbackFunctionPointer;
        break;
    case EXT_INT2:
        EXTI_CallbackPointers[2] = callbackFunctionPointer;
        break;
    }
}

ISR(INT0_vect) {
    if (EXTI_CallbackPointers[0] != NULL_PTR) { EXTI_CallbackPointers[0](); }
}

ISR(INT1_vect) {
    if (EXTI_CallbackPointers[1] != NULL_PTR) { EXTI_CallbackPointers[1](); }
}

ISR(INT2_vect) {
    if (EXTI_CallbackPointers[2] != NULL_PTR) { EXTI_CallbackPointers[2](); }
}