/*==========================================
  KEYPAD.h
  Keypad Driver
============================================
  Type           : Driver Implementation
  Author         : Omar Ezzeldin
==========================================*/

#ifndef KEYPAD_C
#define KEYPAD_C

#include "KEYPAD.h"
#include <util/delay_basic.h>

u8 COL_ARR[KP_NCOL] = {KP_C1, KP_C2, KP_C3, KP_C4};
u8 ROW_ARR[KP_NROW] = {KP_R1, KP_R2, KP_R3, KP_R4};

char KEY_ARR[KP_NROW][KP_NCOL] = {
    {'7', '8', '9', '/'}, {'4', '5', '6', 'X'}, {'1', '2', '3', '-'}, {'*', '0', '=', '+'}};

void KP_Init() {
    DIO_SetPortDirection(KP_PORT, 0b00001111);
    DIO_SetPortValue(KP_PORT, PORT_HIGH);
}

char KP_GetKeyPressed() {
    for (int i = 0; i < KP_NCOL; i++) {
        KP_Init();
        DIO_SetPinValue(KP_PORT, COL_ARR[i], LOW);
        for (int j = 0; j < KP_NCOL; j++) {
            if (DIO_GetPinValue(KP_PORT, ROW_ARR[j]) == 0) {
                u8 delay = 30;
                while (delay--) {
                    _delay_loop_2(4000);
                }
                while (DIO_GetPinValue(KP_PORT, ROW_ARR[j]) == 0) {}
                return KEY_ARR[j][i];
            }
        }
    }
    return 0;
}

#endif /* KEYPAD_C */