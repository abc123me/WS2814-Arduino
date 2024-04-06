#ifndef _WS2814_HAL_H
#define _WS2814_HAL_H

#include "Arduino.h"
#include "avr/io.h"
#include "pins_arduino.h"

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

// Timing configuration (mostly automatic for AVR boards, modifying this is NOT recommended)
#define WS2814_HAL_T1H_PS 300000 // Raw timing values for the WS2814 IC
#define WS2814_HAL_T0H_PS 050000 // Picoseconds used just in case F_CPU > 1GHz
#define WS2814_HAL_T1L_PS 300000
#define WS2814_HAL_T0L_PS 600000

#undef F_CPU

#ifdef F_CPU // Universal timing for any board :)
	#define _WS2814_HAL_PS_PER_CLOCK (1000000000000 / F_CPU)

	#define WS2814_HAL_T1H_NOPS (WS2814_HAL_T1H_PS / _WS2814_HAL_PS_PER_CLOCK)
	#define WS2814_HAL_T0H_NOPS (WS2814_HAL_T0H_PS / _WS2814_HAL_PS_PER_CLOCK)
	#define WS2814_HAL_T1L_NOPS (WS2814_HAL_T1L_PS / _WS2814_HAL_PS_PER_CLOCK)
	#define WS2814_HAL_T0L_NOPS (WS2814_HAL_T0L_PS / _WS2814_HAL_PS_PER_CLOCK)

	#define WS2814_HAL_T1H WS2814_HAL_NOP_CMD(WS2814_HAL_T1H_PS);
	#define WS2814_HAL_T1L WS2814_HAL_NOP_CMD(WS2814_HAL_T1L_PS);
	#define WS2814_HAL_T0H WS2814_HAL_NOP_CMD(WS2814_HAL_T0H_PS);
	#define WS2814_HAL_T0L WS2814_HAL_NOP_CMD(WS2814_HAL_T1L_PS);
#else // Timing (for ATMega328P w/ 20MHz clock)*/
	#pragma warn F_CPU in not defined! Defaulting to 20MHz, if your processor is not 20MHz define it inside of WS2814_HAL.h\
	
	#define WS2814_HAL_T1H WS2814_HAL_NOP_CMD(06); //* asm volatile ("nop\nnop\nnop\nnop\nnop\nnop");
	#define WS2814_HAL_T1L WS2814_HAL_NOP_CMD(06); // asm volatile ("nop\nnop\nnop\nnop\nnop\nnop");
	#define WS2814_HAL_T0H WS2814_HAL_NOP_CMD(01); // asm volatile ("nop\n");
	#define WS2814_HAL_T0L WS2814_HAL_NOP_CMD(12); // asm volatile ("nop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\n");
#endif

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
