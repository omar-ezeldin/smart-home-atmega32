/*==========================================
  DIO.h
  Digital Input/Output Driver
============================================
  Type           : Driver Implementation
  Author         : Omar Ezzeldin
==========================================*/

#include "MCAL/DIO.h"
#include "LIB/BIT_MATH.h"
#include "LIB/STD_TYPES.h"

void DIO_SetPortDirection(u8 PORT_ID, u8 DIRECTION) {
    if (PORT_ID < N_PORTS) {
        switch (PORT_ID) {
        case PA:
            DDRA = DIRECTION;
            break;
        case PB:
            DDRB = DIRECTION;
            break;
        case PC:
            DDRC = DIRECTION;
            break;
        case PD:
            DDRD = DIRECTION;
            break;
        }
    }
}

void DIO_SetPortValue(u8 PORT_ID, u8 VALUE) {
    if (PORT_ID < N_PORTS) {
        switch (PORT_ID) {
        case PA:
            PORTA = VALUE;
            break;
        case PB:
            PORTB = VALUE;
            break;
        case PC:
            PORTC = VALUE;
            break;
        case PD:
            PORTD = VALUE;
            break;
        }
    }
}

u8 DIO_GetPortValue(u8 PORT_ID) {
    if (PORT_ID < N_PORTS) {
        switch (PORT_ID) {
        case PA:
            return PINA;
        case PB:
            return PINB;
        case PC:
            return PINC;
        case PD:
            return PIND;
        }
    }
    return PORT_LOW;
}

void DIO_SetPinDirection(u8 PORT_ID, u8 PIN, u8 DIRECTION) {
    if (PORT_ID < N_PORTS && PIN < N_PINS) {
        switch (PORT_ID) {
        case PA:
            DIRECTION ? SET_BIT(DDRA, PIN) : CLR_BIT(DDRA, PIN);
            break;
        case PB:
            DIRECTION ? SET_BIT(DDRB, PIN) : CLR_BIT(DDRB, PIN);
            break;
        case PC:
            DIRECTION ? SET_BIT(DDRC, PIN) : CLR_BIT(DDRC, PIN);
            break;
        case PD:
            DIRECTION ? SET_BIT(DDRD, PIN) : CLR_BIT(DDRD, PIN);
            break;
        }
    }
}

void DIO_SetPinValue(u8 PORT_ID, u8 PIN, u8 VALUE) {
    if (PORT_ID < N_PORTS && PIN < N_PINS) {
        switch (PORT_ID) {
        case PA:
            VALUE ? SET_BIT(PORTA, PIN) : CLR_BIT(PORTA, PIN);
            break;
        case PB:
            VALUE ? SET_BIT(PORTB, PIN) : CLR_BIT(PORTB, PIN);
            break;
        case PC:
            VALUE ? SET_BIT(PORTC, PIN) : CLR_BIT(PORTC, PIN);
            break;
        case PD:
            VALUE ? SET_BIT(PORTD, PIN) : CLR_BIT(PORTD, PIN);
            break;
        }
    }
}

u8 DIO_GetPinValue(u8 PORT_ID, u8 PIN) {
    if (PORT_ID < N_PORTS) {
        switch (PORT_ID) {
        case PA:
            return GET_BIT(PINA, PIN);
        case PB:
            return GET_BIT(PINB, PIN);
        case PC:
            return GET_BIT(PINC, PIN);
        case PD:
            return GET_BIT(PIND, PIN);
        }
    }
    return LOW;
}

void DIO_TogglePinValue(u8 PORT_ID, u8 PIN) {
    if (PORT_ID < N_PORTS && PIN < N_PINS) {
        switch (PORT_ID) {
        case PA:
            TOG_BIT(PORTA, PIN);
            break;
        case PB:
            TOG_BIT(PORTB, PIN);
            break;
        case PC:
            TOG_BIT(PORTC, PIN);
            break;
        case PD:
            TOG_BIT(PORTD, PIN);
            break;
        }
    }
}
