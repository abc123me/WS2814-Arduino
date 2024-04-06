// RGBW Example for Arduino WS2814 library
// (C) Jeremiah Lowe 2024-2026

#define WS2814_PIN 8
#define WS2814_HAL_LED_PIN_LOW  PORTB &= ~(1 << PORTB0);
#define WS2814_HAL_LED_PIN_HIGH PORTB |= 1 << PORTB0;
#include "WS2814.h" 

#define NUM_LEDS 50
#define COLORS_CNT 4

rgbw_t arr[NUM_LEDS];
rgbw_t colors[COLORS_CNT] = {
	{255, 0, 0, 0},
	{0, 255, 0, 0},
	{0, 0, 255, 0},
	{0, 0, 0, 255}
};

void setup() {
	pinMode(WS2814_PIN, OUTPUT);
	for(uint16_t i = 0; i < NUM_LEDS; i++) {
		arr[i] = {0, 0, 0, 0};
	}
}

uint8_t n = 0;
uint32_t lastTime = 0;
void loop() {
	if(millis() > lastTime + 500) {
		lastTime = millis();
		
		for(uint16_t i = 0; i < NUM_LEDS; i++)
			arr[i] = colors[(i + n) % COLORS_CNT];
		
		ws2814_write(NUM_LEDS, arr);
		
		if(++n > COLORS_CNT) 
			n = 1;
	}
}
