#define F_CPU 16000000UL

#include "LIB/STD_TYPES.h"

#include "HAL/ALARM.h"
#include "HAL/FAN.h"
#include "HAL/FLAME.h"
#include "HAL/LCD.h"
#include "HAL/LDR.h"
#include "HAL/LED.h"
#include "HAL/LM35.h"

// Flame Callback
void FlameCallback() {
    ALARM_SetState(FLAME_IsDetected());

    if (FLAME_IsDetected() == HIGH) {
        LCD_Clear();
        LCD_SendString("Critical alert!");
    } else {
        LCD_Clear();
        LCD_SendString("FAN is OFF");
        LCD_MoveCursor(1, 0);
        LCD_SendString("T:00C LDR:000%");
    }
}

int main() {

    // LCD Initialization
    LCD_Init();
    LCD_SendString("FAN is OFF");
    LCD_MoveCursor(1, 0);
    LCD_SendString("T:00C LDR:000%");

    // Flame Sensor Initialization
    FLAME_SetCallback(FlameCallback);
    FLAME_Init();

    // Components Initialization
    ALARM_Init();
    LDR_Init();
    LED_Init();
    LM35_Init();
    FAN_Init();

    while (1) {
        u8 intensity   = LDR_GetIntensity();
        u8 temperature = LM35_GetTemperature();

        LED_Update(intensity);
        FAN_Update(temperature);

        if (FLAME_IsDetected() == LOW) {
            EXTI_DisableGlobal();
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
            EXTI_EnableGlobal();
        }
    }
}