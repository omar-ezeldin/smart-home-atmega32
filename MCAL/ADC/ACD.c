/*==========================================
  ADC.c
  Analog to Digital Converter
============================================
  Type           : Driver Implementation
  Author         : Omar Ezzeldin
==========================================*/

#include "ADC.h"
#include "LIB/BIT_MATH.h"
#include "MCAL/EXTI.h"

void ADC_Init() {

    switch (ADC_VREF) {

    case AREF:
        CLR_BIT(ADMUX, ADMUX_REFS1);
        CLR_BIT(ADMUX, ADMUX_REFS0);
        break;

    case AVCC:
        CLR_BIT(ADMUX, ADMUX_REFS1);
        SET_BIT(ADMUX, ADMUX_REFS0);
        break;

    case INTERNAL_2_56:
        SET_BIT(ADMUX, ADMUX_REFS1);
        SET_BIT(ADMUX, ADMUX_REFS0);
        break;
    }

    switch (ADC_ADJUSTMENT) {

    case ADC_LEFT_ADJUSTMENT:
        SET_BIT(ADMUX, ADMUX_ADLAR);
        break;

    case ADC_RIGHT_ADJUSTMENT:
        CLR_BIT(ADMUX, ADMUX_ADLAR);
        break;
    }

    switch (ADC_TRIGGERING_SOURCE) {

    case ADC_SINGLE_CONVERSION:
        CLR_BIT(ADCSRA, ADCSRA_ADATE);
        break;

    default:
        SET_BIT(ADCSRA, ADCSRA_ADATE);

        switch (ADC_TRIGGERING_SOURCE) {

        case ADC_FREE_RUNNING:
            CLR_BIT(SFIOR, SFIOR_ADTS2);
            CLR_BIT(SFIOR, SFIOR_ADTS1);
            CLR_BIT(SFIOR, SFIOR_ADTS0);
            break;

        case ADC_ANALOG_COMPARATOR:
            CLR_BIT(SFIOR, SFIOR_ADTS2);
            CLR_BIT(SFIOR, SFIOR_ADTS1);
            SET_BIT(SFIOR, SFIOR_ADTS0);
            break;

        case ADC_EXTI0:
            CLR_BIT(SFIOR, SFIOR_ADTS2);
            SET_BIT(SFIOR, SFIOR_ADTS1);
            CLR_BIT(SFIOR, SFIOR_ADTS0);
            break;

        case ADC_TIM0_CTC:
            CLR_BIT(SFIOR, SFIOR_ADTS2);
            SET_BIT(SFIOR, SFIOR_ADTS1);
            SET_BIT(SFIOR, SFIOR_ADTS0);
            break;

        case ADC_TIM0_OVF:
            SET_BIT(SFIOR, SFIOR_ADTS2);
            CLR_BIT(SFIOR, SFIOR_ADTS1);
            CLR_BIT(SFIOR, SFIOR_ADTS0);
            break;

        case ADC_TIM1_CTC_CHANNEL_B:
            SET_BIT(SFIOR, SFIOR_ADTS2);
            CLR_BIT(SFIOR, SFIOR_ADTS1);
            SET_BIT(SFIOR, SFIOR_ADTS0);
            break;

        case ADC_TIM1_OVF:
            SET_BIT(SFIOR, SFIOR_ADTS2);
            SET_BIT(SFIOR, SFIOR_ADTS1);
            CLR_BIT(SFIOR, SFIOR_ADTS0);
            break;

        case ADC_TIM1_ICU:
            SET_BIT(SFIOR, SFIOR_ADTS2);
            SET_BIT(SFIOR, SFIOR_ADTS1);
            SET_BIT(SFIOR, SFIOR_ADTS0);
            break;
        }
    }

    switch (ADC_STATUS) {

    case ADC_ENABLE:
        SET_BIT(ADCSRA, ADCSRA_ADEN);
        break;

    case ADC_DISABLE:
        CLR_BIT(ADCSRA, ADCSRA_ADEN);
        break;
    }

    ADC_SetPrescaler(ADC_PRESCALLER);

    switch (INT_STATUS) {

    case INT_ENABLE:
        ADC_EnableInterrupt();
        break;

    case INT_DISABLE:
        ADC_DisableInterrupt();
        break;
    }
}

void ADC_StartConversion(u8 channel) {

    ADMUX &= 0xE0;
    ADMUX |= (channel & 0x07);

    SET_BIT(ADCSRA, ADCSRA_ADSC);
}

u16 ADC_GetResult() {

    switch (ADC_ADJUSTMENT) {

    case ADC_RIGHT_ADJUSTMENT: {

        u16 result = 0;

        result = (u16)ADCL;
        result |= (u16)ADCH << 8;

        return result;
    }

    case ADC_LEFT_ADJUSTMENT: {

        u16 result = 0;

        result = (u16)ADCL >> 6;
        result |= (u16)ADCH << 2;

        return result;
    }
    }

    return 0;
}

u16 ADC_Read(u8 channel) {
    SET_BIT(ADCSRA, ADCSRA_ADIF);
    ADC_StartConversion(channel);

    while (GET_BIT(ADCSRA, ADCSRA_ADIF) == 0) {}

    return ADC_GetResult();
}

void ADC_SetPrescaler(u8 prescaler) {

    switch (prescaler) {

    case ADC_PRE_2:
        CLR_BIT(ADCSRA, ADCSRA_ADPS2);
        CLR_BIT(ADCSRA, ADCSRA_ADPS1);
        CLR_BIT(ADCSRA, ADCSRA_ADPS0);
        break;

    case ADC_PRE_4:
        CLR_BIT(ADCSRA, ADCSRA_ADPS2);
        SET_BIT(ADCSRA, ADCSRA_ADPS1);
        CLR_BIT(ADCSRA, ADCSRA_ADPS0);
        break;

    case ADC_PRE_8:
        CLR_BIT(ADCSRA, ADCSRA_ADPS2);
        SET_BIT(ADCSRA, ADCSRA_ADPS1);
        SET_BIT(ADCSRA, ADCSRA_ADPS0);
        break;

    case ADC_PRE_16:
        SET_BIT(ADCSRA, ADCSRA_ADPS2);
        CLR_BIT(ADCSRA, ADCSRA_ADPS1);
        CLR_BIT(ADCSRA, ADCSRA_ADPS0);
        break;

    case ADC_PRE_32:
        SET_BIT(ADCSRA, ADCSRA_ADPS2);
        CLR_BIT(ADCSRA, ADCSRA_ADPS1);
        SET_BIT(ADCSRA, ADCSRA_ADPS0);
        break;

    case ADC_PRE_64:
        SET_BIT(ADCSRA, ADCSRA_ADPS2);
        SET_BIT(ADCSRA, ADCSRA_ADPS1);
        CLR_BIT(ADCSRA, ADCSRA_ADPS0);
        break;

    case ADC_PRE_128:
        SET_BIT(ADCSRA, ADCSRA_ADPS2);
        SET_BIT(ADCSRA, ADCSRA_ADPS1);
        SET_BIT(ADCSRA, ADCSRA_ADPS0);
        break;
    }
}

void ADC_EnableInterrupt() {

    SET_BIT(ADCSRA, ADCSRA_ADIE);
}

void ADC_DisableInterrupt() {

    CLR_BIT(ADCSRA, ADCSRA_ADIE);
}

static void (*ADC_Callback)(void) = NULL_PTR;

void ADC_SetCallback(void (*callbackFunctionPointer)(void)) {

    ADC_Callback = callbackFunctionPointer;
}

ISR(ADC_vect) {

    if (ADC_Callback != NULL_PTR) { ADC_Callback(); }
}
