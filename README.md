# Smart Home Automation

ATmega32 smart-home project using an LDR, LM35 temperature sensor, flame sensor,
16x2 LCD, three indicator LEDs, a buzzer, and an H-bridge-controlled fan.

## Documentation

The complete source and hardware reference is in
[`docs/Codebase.md`](docs/Codebase.md). It covers:

- Layered architecture and source tree
- MCU pin assignments
- ADC, LDR calibration, LM35, flame, LED, LCD, and fan behavior
- Timer0 PWM and INT0 interrupt usage
- Build instructions
- Proteus wiring requirements and known hardware caveats

## Build

The project uses CMake and the AVR-GCC toolchain. Install CMake, Ninja, and
the AVR-GCC tools first. From the repository root:

```sh
cmake --preset Smart_Home_default_conf \
  -S cmake/Smart_Home/default
cmake --build _build/Smart_Home/default --parallel
```

The AVR ELF and listing are generated under `out/Smart_Home/`.

## Main runtime

`main.c` initializes the LCD, LDR, LEDs, LM35, flame sensor, and fan. The main
loop reads the two ADC sensors, updates the LEDs and fan, and refreshes normal
LCD data. Flame detection is maintained by the INT0 interrupt driver; the LCD
is not accessed from the ISR.
