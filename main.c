/*==========================================
  main.c
============================================*/

#define F_CPU 16000000UL

#include "LIB/STD_TYPES.h"

#include "HAL/FAN.h"
#include "HAL/FLAME.h"
#include "HAL/LCD.h"
#include "HAL/LDR.h"
#include "HAL/LED.h"
#include "HAL/LM35.h"

/*==========================================
MAIN
==========================================*/

int main() {
    /* Initialize LCD */
    LCD_Init();
    LCD_SendString("FAN is OFF");
    LCD_MoveCursor(1, 0);
    LCD_SendString("T:00C LDR:000%");

    /* Initialize lighting control */
    LDR_Init();
    LED_Init();
    LM35_Init();
    FLAME_Init();
    FAN_Init();

    while (1) {
        static u8 previousFlameState = LOW;
        u16       ldrValue           = LDR_Read();
        u8        intensity          = LDR_GetIntensity(ldrValue);
        u16       lm35Value          = LM35_Read();
        u8        temperature        = LM35_GetTemperature(lm35Value);

        LED_Update(intensity);
        FAN_Update(temperature);

        if (FLAME_IsDetected() != previousFlameState) {
            LCD_Clear();
            if (FLAME_IsDetected() == HIGH) {
                LCD_SendString("Critical alert!");
            } else {
                if (FAN_IsOn() == HIGH) {
                    LCD_SendString("FAN is ON");
                } else {
                    LCD_SendString("FAN is OFF");
                }
                LCD_MoveCursor(1, 0);
                LCD_SendString("T:00C LDR:000%");
            }
            previousFlameState = FLAME_IsDetected();
        }

        if (FLAME_IsDetected() == LOW) {
            LCD_MoveCursor(0, 0);
            if (FAN_IsOn() == HIGH) {
                LCD_SendString("FAN is ON ");
            } else {
                LCD_SendString("FAN is OFF");
            }
            LCD_MoveCursor(1, 2);
            LCD_Data((temperature / 10) + '0');
            LCD_Data((temperature % 10) + '0');
            LCD_MoveCursor(1, 10);
            LCD_Data((intensity / 100) + '0');
            LCD_Data(((intensity / 10) % 10) + '0');
            LCD_Data((intensity % 10) + '0');
        }
    }
}