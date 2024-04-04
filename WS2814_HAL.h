#ifndef _WS2814_HAL_H
#define _WS2814_HAL_H

#include "Arduino.h"
#include "avr/io.h"

// GPIO (set to use pin 8 of Arduino Uno, PB0)
#define WS2814_HAL_LED_PIN_LOW PORTB &= ~(1 << PORTB0);
#define WS2814_HAL_LED_PIN_HIGH PORTB |= 1 << PORTB0;

// Timing (for ATMega328P w/ 20MHz clock)
#define WS2814_HAL_T1H asm volatile ("nop\nnop\nnop\nnop\nnop\nnop");
#define WS2814_HAL_T1L asm volatile ("nop\nnop\nnop\nnop\nnop\nnop");
#define WS2814_HAL_T0H asm volatile ("nop\n");
#define WS2814_HAL_T0L asm volatile ("nop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\n");
#define WS2814_HAL_DELAY_RESET delayMicroseconds(300);

//Interrupts (for any Atmel AVR architecture board)
#define WS2814_HAL_INTERRUPTS asm volatile ("sei\n"); // probably should turn them back on
#define WS2814_HAL_NO_INTERRUPTS asm volatile ("cli\n"); // also no interrupts :P

// End of configuration section, modify at your own risk!

#define WS2814_HAL_SEND_BIT_MACRO(n) {\
	if(b & n) {\
		WS2814_HAL_LED_PIN_HIGH\
		WS2814_HAL_T1H\
		WS2814_HAL_LED_PIN_LOW\
		WS2814_HAL_T1L\
	} else {\
		WS2814_HAL_LED_PIN_HIGH\
		WS2814_HAL_T0H\
		WS2814_HAL_LED_PIN_LOW\
		WS2814_HAL_T0L\
	}\
}

#endif
