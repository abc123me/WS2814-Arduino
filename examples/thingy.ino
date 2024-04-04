#include "WS2814.h" // See WS2814_HAL.h for configuration

#define NUM_LEDS 50

rgbw_t arr[NUM_LEDS];

void setup() {
	pinMode(8, OUTPUT); // REMEMBER TO DO THIS
	
	for(uint16_t i = 0; i < NUM_LEDS; i++) {
		arr[i] = {0, 0, 0, 0};
	}
}

float n = 0;
uint32_t lastTime = 0;
void loop() {
	if(millis() > lastTime + 50) {
		lastTime = millis();
		
		for(uint16_t i = 0; i < NUM_LEDS; i++) {
			float t = n + i / 3.0f;
			float a = ((1.0f + sin(t)) / 2.0f) * (255 - 200) + 200;
			float d = ((1.0f + cos(t)) / 2.0f) * 50.0f;
			uint8_t ac = round(a);
			uint8_t dc = round(d);
			arr[i] = {ac, dc, 0, 0};
		}
		ws2814_write(NUM_LEDS, arr);
		n += PI / 20;
		if(n > 2 * PI) n -= 2 * PI;
	}
}
