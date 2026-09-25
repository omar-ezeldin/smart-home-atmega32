# Smart Home Codebase Reference

## 1. Scope

This repository implements the 2026 ATmega32 smart-home project described in
`reference/Embedded_Final_Project.pdf`. The application combines:

- Nonlinear LDR light measurement and three-level LED indication
- LM35 temperature measurement
- Temperature-controlled H-bridge fan control
- Optional Timer0 PWM fan-speed control
- INT0-based flame detection and buzzer alarm
- 16x2 LCD status display

The project follows the intended layered structure:

```text
Application
  main.c

HAL
  LDR, LM35, LED, FAN, FLAME, LCD

MCAL
  ADC, DIO, EXTI, TIMER

LIB
  STD_TYPES, BIT_MATH
```

The HAL drivers contain device behavior and pin configuration. The MCAL
drivers access ATmega32 peripherals and registers. `main.c` coordinates the
devices and owns the application loop.

## 2. Source tree

| Path | Responsibility |
|---|---|
| `main.c` | Initializes the system, reads sensors, updates outputs, and manages normal/alert LCD screens. |
| `LIB/STD_TYPES.h` | Project aliases such as `u8`, `u16`, `u32`, and `f64`. |
| `LIB/BIT_MATH.h` | `SET_BIT`, `CLR_BIT`, `TOG_BIT`, and `GET_BIT` macros. |
| `MCAL/DIO` | ATmega32 GPIO register definitions and pin/port operations. |
| `MCAL/ADC` | ADC reference, channel selection, conversion, result reading, and prescaler configuration. |
| `MCAL/EXTI` | INT0/INT1/INT2 sense control, enable/disable, callbacks, and ISR vectors. |
| `MCAL/TIMER/TIMER0` | Timer0 mode, clock selection, output compare register, and timer control. |
| `MCAL/TIMER/TIMER1` | Timer1 driver retained for future timer features. |
| `MCAL/TIMER/TIMER2` | Timer2 driver retained for future timer features. |
| `HAL/LCD` | 8-bit 16x2 LCD commands, initialization, cursor movement, and text output. |
| `HAL/LDR` | LDR ADC channel, raw reads, voltage conversion, calibration, and interpolation. |
| `HAL/LM35` | LM35 ADC channel, voltage conversion, and Celsius conversion. |
| `HAL/LED` | RGB LED initialization and light-intensity output bands. |
| `HAL/FAN` | H-bridge direction control and Timer0 PWM fan speed. |
| `HAL/FLAME` | INT0 flame state tracking and buzzer output. |
| `HAL/KEYPAD` | Existing standalone keypad driver; not used by the current application. |
| `HAL/SEVSEG` | Existing standalone seven-segment driver; not used by the current application. |

The one-level headers such as `HAL/LDR.h` and `MCAL/ADC.h` are import headers.
They include the implementation-level driver header in the corresponding
subdirectory and preserve the project's include convention.

`_build/`, `out/`, and generated files under `cmake/` are build artifacts or
generated project files. They are not application source.

## 3. Hardware and pin map

The following assignments come from the project PDF and the driver headers.

| Device | Signal | ATmega32 connection |
|---|---|---|
| LDR | Analog output | `PA0 / ADC0` |
| LM35 | `VOUT` | `PA1 / ADC1` |
| LCD | RS | `PD0` |
| LCD | Enable | `PD1` |
| LCD | Data bus D0-D7 | `PORTC` |
| Fan H-bridge | IN1 | `PB0` |
| Fan H-bridge | IN2 | `PB1` |
| Fan H-bridge | Enable1 / PWM | `PB3 / OC0` |
| RGB LED | Red | `PB5` |
| RGB LED | Green | `PB6` |
| RGB LED | Blue | `PB7` |
| Flame sensor | Digital output | `PD2 / INT0` |
| Buzzer driver control | Transistor control | `PD3` |

The LCD R/W input is expected to be grounded because the driver only writes to
the display.

The flame and buzzer signals intentionally use adjacent Port D pins that do not
overlap the LCD control pins. The fan PWM pin is separate from the three LED
pins.

## 4. ADC configuration

The ADC driver in `MCAL/ADC/ADC.h` is configured for:

```text
Reference: AVCC
Reference value used by conversions: 5000 mV
Resolution: 10-bit, values 0..1023
Result: right-adjusted
Trigger: single conversion
Prescaler: 128
```

`ADC_Read(channel)` clears the ADC interrupt flag, selects the channel, starts
one conversion, waits for completion, and returns the 10-bit result.

The LDR and LM35 drivers both use this shared ADC peripheral. Each calls
`ADC_Init()` during initialization; the configuration is identical and the
last initialization leaves the same ADC setup active.

## 5. LDR driver

### API

```c
void LDR_Init();
u16  LDR_Read();
u16  LDR_GetVoltage(u16 value);
u8   LDR_GetIntensity(u16 value);
```

`LDR_Read()` returns the raw ADC result. `LDR_GetVoltage()` converts it using:

```text
voltage_mV = adc_value * 5000 / 1023
```

The light response is nonlinear, so the driver does not normalize voltage
directly to a percentage. It uses the measured transfer characteristic:

| Voltage | Intensity |
|---:|---:|
| 0.0049 V | 0% |
| 0.0248 V | 11.11% |
| 0.0495 V | 22.22% |
| 0.0980 V | 33.33% |
| 0.2381 V | 44.44% |
| 0.4545 V | 55.56% |
| 0.8333 V | 66.67% |
| 1.6666 V | 77.78% |
| 2.4999 V | 88.89% |
| 3.3330 V | 100% |

The implementation stores voltages in millivolts and intensities in hundredths
of a percent. For an input between two points, it performs integer piecewise
linear interpolation between the surrounding points and rounds the final
percentage to the nearest integer. Inputs below the first point clamp to 0%;
inputs above the final point clamp to 100%.

The raw ADC result remains separate from the calibrated intensity so it can be
displayed or logged during future recalibration.

## 6. LED driver

`LED_Init()` configures the RGB LED pins as outputs and switches them off.
`LED_Update(intensity)` applies the required application bands:

| Intensity | Red | Green | Blue |
|---:|---|---|---|
| `< 15%` | ON | ON | ON |
| `15–50%` | ON | ON | OFF |
| `51–70%` | ON | OFF | OFF |
| `> 70%` | OFF | OFF | OFF |

The thresholds are named in `HAL/LED/LED.h`. The LEDs are active-high in the
current implementation.

## 7. LM35 driver

### API

```c
void LM35_Init();
u16  LM35_Read();
u16  LM35_GetVoltage(u16 value);
u8   LM35_GetTemperature(u16 value);
```

The LM35 is connected to `PA1/ADC1`. The driver uses the LM35 scale of
`10 mV/°C`:

```text
temperature_C = voltage_mV / 10
```

The current return type is `u8`, so the application displays whole,
non-negative Celsius degrees.

## 8. Fan driver and PWM

`FAN_Init()` configures the H-bridge control pins and initializes Timer0 for
Fast PWM. The motor direction is forward when:

```text
IN1 = HIGH
IN2 = LOW
```

Below 25°C, the driver stops Timer0, disconnects the OC0 output, drives the
enable low, and records the fan as off.

The optional bonus behavior is enabled:

| Temperature | PWM duty |
|---:|---:|
| `< 25°C` | 0%, fan off |
| `25–29°C` | 25% |
| `30–34°C` | 50% |
| `35–39°C` | 75% |
| `>= 40°C` | 100% |

The duty values are written through `TIMER0_SetOutputCompareValue()` as 64,
128, 191, and 255. Timer0 uses the non-inverting OC0 mode and a prescaler of
64. These Timer0 mode, output mode, and prescaler choices are compile-time
configuration in `MCAL/TIMER/TIMER0/TIMER0.h`; they are not runtime variables
and are not changed by the FAN driver. `FAN_IsOn()` reports the logical fan
state maintained by the driver.

## 9. Flame driver and alarm

The flame sensor output is connected to `PD2/INT0`. The confirmed signal
polarity is:

```text
No flame: LOW
Flame:    HIGH
```

`FLAME_Init()`:

1. Configures `PD2` as an input.
2. Configures `PD3` as a buzzer-driver output.
3. Samples the initial flame state.
4. Registers the INT0 callback.
5. Configures INT0 for logical changes.
6. Enables INT0 and global interrupts.

The ISR callback reads `PD2`, updates the volatile flame state, and writes the
same state to `PD3`. The callback does not access the LCD. `main.c` observes
`FLAME_IsDetected()` and changes the LCD between the normal screen and
`Critical alert!`.

The buzzer output is a transistor-driver control signal, not a direct
microcontroller power connection. For the documented BC547 low-side circuit:

```text
PD3 -> base resistor -> BC547 base
base -> pull-down resistor -> GND
BC547 emitter -> GND
BC547 collector -> buzzer negative
buzzer positive -> VCC
```

The MCU, transistor circuit, and buzzer must share ground. The BC547 pin
orientation must match the Proteus symbol. If the LCD alarm works but the
buzzer does not, verify the transistor base voltage and collector voltage
before changing firmware.

## 10. LCD driver and application display

The LCD is initialized in 8-bit, two-line mode:

```text
RS: PD0
E:  PD1
Data: PORTC
```

The normal application screen is:

```text
FAN is ON
FAN is OFF
T:xxC LDR:xxx%
```

The second row is intentionally compact so the temperature and LDR value fit
on a 16-character display. During flame detection, the first row is replaced
with `Critical alert!`; normal sensor updates are suspended until the alert
ends.

LCD operations are performed in the main loop. They are never performed inside
the flame ISR.

## 11. Application flow

`main()` performs the following initialization:

```text
LCD_Init
LDR_Init
LED_Init
LM35_Init
FLAME_Init
FAN_Init
```

The main loop then:

1. Reads the raw LDR ADC value and calculates calibrated intensity.
2. Reads the raw LM35 ADC value and calculates Celsius temperature.
3. Updates the RGB LEDs.
4. Updates the fan direction and PWM duty.
5. Detects flame-state changes maintained by INT0.
6. Refreshes the normal LCD values when no flame is active.

The flame sensor itself is not polled in the main loop. The loop only reads the
driver's interrupt-maintained state.

## 12. Build and outputs

The generated project uses an AVR-GCC toolchain and targets `ATmega32`.

From the repository root:

```sh
cmake --preset Smart_Home_default_conf \
  -S cmake/Smart_Home/default
cmake --build _build/Smart_Home/default --parallel
```

Generated outputs include:

```text
out/Smart_Home/default.elf
out/Smart_Home/default.lss
out/Smart_Home/default.hex
```

The current build has been verified to compile and link for the ATmega32.

## 13. Clock configuration note

The project requirements state a 16 MHz system frequency, while the current
build configuration defines `F_CPU=8000000UL` and `main.c` also declares 8 MHz.
The Timer0 support header assumes 16 MHz for its timing calculations.

This inconsistency must match the actual Proteus crystal/clock configuration
before final hardware or timing claims are made. It affects:

- LCD delay routines
- Timer0 PWM frequency
- Any future timer delay calculations

Do not change only one of these values. Align the schematic clock, compiler
definition, application `F_CPU`, and timer assumptions together.

## 14. Existing but unused drivers

`HAL/KEYPAD` and `HAL/SEVSEG` are implemented reusable drivers but are not part
of the current smart-home runtime. The Timer1 and Timer2 MCAL drivers are also
retained for future components. They should not be removed merely because the
current application does not use them.

## 15. Validation checklist

Before a final Proteus demonstration:

- Confirm LDR values follow the ten-point calibration curve.
- Exercise all four LED bands.
- Test LM35 values below and above 25°C.
- Test fan PWM at 25°C, 30°C, 35°C, and 40°C.
- Trigger flame detection and confirm INT0, `Critical alert!`, and buzzer output.
- Remove the flame and confirm buzzer shutdown and normal LCD recovery.
- Measure `PD3`, the BC547 base, and collector if the buzzer remains silent.
- Verify the actual MCU clock matches the software configuration.
