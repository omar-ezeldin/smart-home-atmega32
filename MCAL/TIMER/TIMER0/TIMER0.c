/*==========================================
  TIMER0.h
  Timer 0 Driver
============================================
  Type           : Driver Implementation
  Author         : Omar Ezzeldin
==========================================*/

#include "TIMER0.h"
#include "LIB/BIT_MATH.h"
#include "LIB/STD_TYPES.h"
#include "MCAL/EXTI.h"

/*==========================================
FUNCTION IMPLEMENTATIONS
==========================================*/

void TIMER0_Init() {
    TCNT0       = 0;
    OCR0        = 0;
    switch (TIMER0_MODE) {
    case TIMER_MD_NORMAL:
        CLR_BIT(TCCR0, WGM00);
        CLR_BIT(TCCR0, WGM01);
        break;
    case TIMER_MD_PHASECORRECT:
        SET_BIT(TCCR0, WGM00);
        CLR_BIT(TCCR0, WGM01);
        break;
    case TIMER_MD_CTC:
        CLR_BIT(TCCR0, WGM00);
        SET_BIT(TCCR0, WGM01);
        break;
    case TIMER_MD_FASTPWM:
        SET_BIT(TCCR0, WGM00);
        SET_BIT(TCCR0, WGM01);
        break;
    }
    switch (TIMER0_OUTPUT_MODE) {
    case TIMER0_OUTPUT_DISCONNECTED:
        CLR_BIT(TCCR0, COM00);
        CLR_BIT(TCCR0, COM01);
        break;
    case TIMER0_OUTPUT_TOGGLE:
        SET_BIT(TCCR0, COM00);
        CLR_BIT(TCCR0, COM01);
        break;
    case TIMER0_OUTPUT_NON_INVERTING:
        CLR_BIT(TCCR0, COM00);
        SET_BIT(TCCR0, COM01);
        break;
    case TIMER0_OUTPUT_INVERTING:
        SET_BIT(TCCR0, COM00);
        SET_BIT(TCCR0, COM01);
        break;
    }
}

void TIMER0_Start() {
    switch (TIMER0_PRESCALER) {
    case TIMER_PS_1:
        SET_BIT(TCCR0, CS00);
        CLR_BIT(TCCR0, CS01);
        CLR_BIT(TCCR0, CS02);
        break;
    case TIMER_PS_8:
        CLR_BIT(TCCR0, CS00);
        SET_BIT(TCCR0, CS01);
        CLR_BIT(TCCR0, CS02);
        break;
    case TIMER_PS_64:
        SET_BIT(TCCR0, CS00);
        SET_BIT(TCCR0, CS01);
        CLR_BIT(TCCR0, CS02);
        break;
    case TIMER_PS_256:
        CLR_BIT(TCCR0, CS00);
        CLR_BIT(TCCR0, CS01);
        SET_BIT(TCCR0, CS02);
        break;
    case TIMER_PS_1024:
        SET_BIT(TCCR0, CS00);
        CLR_BIT(TCCR0, CS01);
        SET_BIT(TCCR0, CS02);
        break;
    case TIMER_PS_EXTCLK_FALLEDGE:
        CLR_BIT(TCCR0, CS00);
        SET_BIT(TCCR0, CS01);
        SET_BIT(TCCR0, CS02);
        break;
    case TIMER_PS_EXTCLK_RAISEDGE:
        SET_BIT(TCCR0, CS00);
        SET_BIT(TCCR0, CS01);
        SET_BIT(TCCR0, CS02);
        break;
    }
}

void TIMER0_Stop() {
    CLR_BIT(TCCR0, CS00);
    CLR_BIT(TCCR0, CS01);
    CLR_BIT(TCCR0, CS02);
}

void TIMER0_SetOutputCompareValue(u8 value) {
    OCR0 = value;
}

void TIMER0_EnableInterrupt() {
    switch (TIMER0_MODE) {
    case TIMER_MD_NORMAL:
        SET_BIT(TIMSK, TOIE0);
        break;
    case TIMER_MD_CTC:
        SET_BIT(TIMSK, OCIE0);
        break;
    }
}

void TIMER0_DisableInterrupt() {
    switch (TIMER0_MODE) {
    case TIMER_MD_NORMAL:
        CLR_BIT(TIMSK, TOIE0);
        break;
    case TIMER_MD_CTC:
        CLR_BIT(TIMSK, OCIE0);
        break;
    }
}

u32 TIMER0_GetRealPrescaler() {
    switch (TIMER0_PRESCALER) {
    case TIMER_PS_1:
        return 1;
    case TIMER_PS_8:
        return 8;
    case TIMER_PS_64:
        return 64;
    case TIMER_PS_256:
        return 256;
    case TIMER_PS_1024:
        return 1024;
    default:
        return 0;
    }
}

static void (*TIMER0_OVF_Callback)(void) = NULL_PTR;

void TIMER0_SetCallback(void (*callbackFunctionPointer)(void)) {
    TIMER0_OVF_Callback = callbackFunctionPointer;
}

static volatile u32 TIMER0_OverflowTarget  = 0;
static volatile u32 TIMER0_OverflowCounter = 0;
static volatile u8  TIMER0_Preload         = 0;

void TIMER0_SetTime(u32 time) {
    u32 p          = TIMER0_GetRealPrescaler();
    f64 tickTime   = (f64)p / (TIMER_FCPU * 1000.0);
    u32 totalTicks = (u32)(time / tickTime);

    switch (TIMER0_MODE) {
    case TIMER_MD_NORMAL:
        TIMER0_OverflowCounter = 0;
        TIMER0_OverflowTarget  = (totalTicks + 255) / 256;
        TIMER0_Preload         = 256 - (totalTicks % 256);
        TCNT0                  = TIMER0_Preload;
        break;

    case TIMER_MD_CTC:
        break;
    }
}

ISR(TIMER0_OVF_vect) {
    if (TIMER0_OverflowCounter < TIMER0_OverflowTarget) {
        TIMER0_OverflowCounter++;
        if (TIMER0_OverflowCounter == TIMER0_OverflowTarget) {
            if (TIMER0_OVF_Callback != NULL_PTR) { TIMER0_OVF_Callback(); }
            TIMER0_OverflowCounter = 0;
            TCNT0                  = TIMER0_Preload;
        }
    }
}