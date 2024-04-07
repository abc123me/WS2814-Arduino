# WS28XX Embedded library
This is a library for the WS2812 and WS2814 LED strips, it was originally intended for Arduino but should work on other platforms.

## Support
This driver currently only supports the Atmel AVR line, and is *specifically* for the ATMega328P with a 20MHz clock!

*However, * it is trivial to modify the below code in order to achieve support for whatever CPU you want!

To use this with your board, change the following macros in `WS2814_HAL.h`:
```
// -----------------------------------------------------------
// |           Beginning of configuration section!           |
// -----------------------------------------------------------

// GPIO (set to use pin 8 of Arduino Uno, PB0)
#define WS2814_HAL_LED_PIN_LOW PORTB &= ~(1 << PORTB0);
#define WS2814_HAL_LED_PIN_HIGH PORTB |= (1 << PORTB0);

// Anything beyond this point can be changed, but probably shouldn't be

// Interrupts (for any Atmel AVR architecture board)
#define WS2814_HAL_NO_INTERRUPTS noInterrupts(); // no interrupts in critical timing
#define WS2814_HAL_INTERRUPTS interrupts(); // probably should turn them back on :P
#define WS2814_HAL_DELAY_RESET delayMicroseconds(300);
#define WS2814_HAL_NOP_CMD(n) __builtin_avr_delay_cycles(n);

// -----------------------------------------------------------
// | End of configuration section, modify at your own risk!  |
// -----------------------------------------------------------
```
Remember, it's not pretty but it works, and this is a free driver for an obscure chip that not many use with the Arduino

If you want features added or need support for different MCUs, please post an issue on GitHub and i'll look into it as soon as I can!

Any donations would be greatly appreciated: https://www.buymeacoffee.com/kn4hji

## Future plans (in no order)
- Make a WS2814 object that can be instantiated with a pin number and led count / rgbw_t array pointer
- Optimize LED strip timings, they're kinda guessed but they seem to work
- Support for WS2812 and WS2811, FastLED is kinda bloated (and I don't like it)
- STM32 and SAMD21 support, maybe even a linux kernel driver?!
