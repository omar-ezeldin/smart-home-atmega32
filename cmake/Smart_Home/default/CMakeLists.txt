cmake_minimum_required(VERSION 3.24.0)

project(Smart_Home_default_project LANGUAGES C ASM)

get_filename_component(PROJECT_ROOT "${CMAKE_CURRENT_LIST_DIR}/../../.." ABSOLUTE)

set(SOURCES
    "${PROJECT_ROOT}/HAL/ALARM/ALARM.c"
    "${PROJECT_ROOT}/HAL/FAN/FAN.c"
    "${PROJECT_ROOT}/HAL/FLAME/FLAME.c"
    "${PROJECT_ROOT}/HAL/KEYPAD/KEYPAD.c"
    "${PROJECT_ROOT}/HAL/LCD/LCD.c"
    "${PROJECT_ROOT}/HAL/LDR/LDR.c"
    "${PROJECT_ROOT}/HAL/LED/LED.c"
    "${PROJECT_ROOT}/HAL/LM35/LM35.c"
    "${PROJECT_ROOT}/HAL/SEVSEG/SEVSEG.c"
    "${PROJECT_ROOT}/MCAL/ADC/ACD.c"
    "${PROJECT_ROOT}/MCAL/DIO/DIO.c"
    "${PROJECT_ROOT}/MCAL/EXTI/EXTI.c"
    "${PROJECT_ROOT}/MCAL/TIMER/TIMER0/TIMER0.c"
    "${PROJECT_ROOT}/MCAL/TIMER/TIMER1/TIMER1.c"
    "${PROJECT_ROOT}/MCAL/TIMER/TIMER2/TIMER2.c"
    "${PROJECT_ROOT}/main.c"
)

add_executable(Smart_Home_default_image ${SOURCES})

set_target_properties(Smart_Home_default_image PROPERTIES
    OUTPUT_NAME "default"
    SUFFIX ".elf"
    RUNTIME_OUTPUT_DIRECTORY "${PROJECT_ROOT}/out/Smart_Home"
)

target_include_directories(Smart_Home_default_image PRIVATE "${PROJECT_ROOT}")

target_compile_options(Smart_Home_default_image PRIVATE
    -mmcu=atmega32
    -g
    -gdwarf-2
    -funsigned-char
    -funsigned-bitfields
    -O1
    -ffunction-sections
    -fdata-sections
    -fpack-struct
    -fshort-enums
    -Wall
)

target_compile_definitions(Smart_Home_default_image PRIVATE
    __ATmega32__
    default=default
)

set_source_files_properties(
    "${PROJECT_ROOT}/HAL/LCD/LCD.c"
    PROPERTIES COMPILE_DEFINITIONS F_CPU=8000000UL
)

target_link_options(Smart_Home_default_image PRIVATE
    -mmcu=atmega32
    -Wl,-Map=${CMAKE_BINARY_DIR}/mem.map
    -Wl,--gc-sections
)

add_custom_command(
    TARGET Smart_Home_default_image POST_BUILD
    COMMAND ${CMAKE_OBJCOPY}
        --output-target=ihex
        "$<TARGET_FILE:Smart_Home_default_image>"
        "${PROJECT_ROOT}/out/Smart_Home/default.hex"
    COMMAND ${CMAKE_OBJCOPY}
        --only-section=.eeprom
        --change-section-lma .eeprom=0
        --no-change-warnings
        --output-target=ihex
        "$<TARGET_FILE:Smart_Home_default_image>"
        "${PROJECT_ROOT}/out/Smart_Home/default.eep"
    COMMAND ${CMAKE_OBJDUMP}
        --disassemble --wide --demangle --line-numbers --section-headers
        --source "$<TARGET_FILE:Smart_Home_default_image>"
        > "${PROJECT_ROOT}/out/Smart_Home/default.lss"
    COMMAND ${CMAKE_OBJCOPY}
        --output-target=srec
        --remove-section=.eeprom
        --remove-section=.fuse
        --remove-section=.lock
        --remove-section=.signature
        "$<TARGET_FILE:Smart_Home_default_image>"
        "${PROJECT_ROOT}/out/Smart_Home/default.srec"
    COMMAND ${CMAKE_OBJCOPY}
        --only-section=.user_signatures
        --change-section-lma .user_signatures=0
        --no-change-warnings
        --output-target=ihex
        "$<TARGET_FILE:Smart_Home_default_image>"
        "${PROJECT_ROOT}/out/Smart_Home/default.usersignatures"
)
