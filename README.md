# WS2814-Arduino
WS2814 driver library for Arduino

## Support
This driver currently only supports the Atmel AVR line, and is *specifically* for the ATMega328P with a 20MHz clock!

*However, * it is trivial to modify the below code in order to achieve support for whatever CPU you want!

To use this with your board, change the following macros in `WS2814_HAL.h`:
```
// GPIO (set to use pin 8 of Arduino Uno, PB0)
#define WS2814_HAL_LED_PIN_LOW PORTB &= ~(1 << PORTB0);
#define WS2814_HAL_LED_PIN_HIGH PORTB |= 1 << PORTB0;

// Timing (for ATMega328P w/ 20MHz clock)
#define WS2814_HAL_T1H asm volatile ("nop\nnop\nnop\nnop\nnop\nnop");
#define WS2814_HAL_T1L asm volatile ("nop\nnop\nnop\nnop\nnop\nnop");
#define WS2814_HAL_T0H asm volatile ("nop\n");
#define WS2814_HAL_T0L asm volatile ("nop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\n");

//Interrupts (for any Atmel AVR architecture board)
#define WS2814_HAL_INTERRUPTS asm volatile ("sei\n"); // probably should turn them back on
#define WS2814_HAL_NO_INTERRUPTS asm volatile ("cli\n"); // also no interrupts :P
```
Remember, it's not pretty but it works, and this is a free driver for an obscure chip that not many use with the Arduino

If you want features added or support for different MCUs, please post an issue, and donations would be greatly appreciated:
https://www.buymeacoffee.com/kn4hji
