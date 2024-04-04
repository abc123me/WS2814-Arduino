#include "WS2814.h"

#include "WS2814_HAL.h"

inline volatile void ws2814_hal_writeByte(uint8_t b) { // DO NOT OPTIMIZE
  WS2814_HAL_NO_INTERRUPTS // also no interrupts :P
  // BEGIN TIMING CRITICAL CODE
  WS2814_HAL_SEND_BIT_MACRO(128);
  WS2814_HAL_SEND_BIT_MACRO(64);
  WS2814_HAL_SEND_BIT_MACRO(32);
  WS2814_HAL_SEND_BIT_MACRO(16);
  WS2814_HAL_SEND_BIT_MACRO(8);
  WS2814_HAL_SEND_BIT_MACRO(4);
  WS2814_HAL_SEND_BIT_MACRO(2);
  WS2814_HAL_SEND_BIT_MACRO(1);
  WS2814_HAL_LED_PIN_LOW
  // END TIMING CRITICAL CODE
  WS2814_HAL_INTERRUPTS // Might wannas turn them back on
}
void ws2814_hal_reset() {
  WS2814_HAL_LED_PIN_LOW
  WS2814_HAL_DELAY_RESET
}
void ws2814_write(uint16_t num, struct rgbw_t* dat) {
  for(uint16_t i = 0; i < num; i++) {
    ws2814_hal_writeByte(dat[i].w);
    ws2814_hal_writeByte(dat[i].r);
    ws2814_hal_writeByte(dat[i].g);
    ws2814_hal_writeByte(dat[i].b);
  }
  ws2814_hal_reset();
}
