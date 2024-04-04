#ifndef _WS2814_H
#define _WS2814_H

#include "stdint.h"

struct __attribute__  ((packed)) rgbw_t {
	uint8_t r, g, b, w;
};

void ws2814_hal_reset();
void ws2814_write(uint16_t num, struct rgbw_t* dat);

#endif
 
