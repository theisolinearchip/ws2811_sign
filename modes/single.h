#include <util/delay.h>

void red_init() {

	for (int i = 0; i < LEDS_LENGTH; i++) {
		led_strip[i] = colors[current_color];
	}

}

void red_step() {
	
	for (int i = 0; i < LEDS_LENGTH; i++) {
		led_strip[i] = colors[current_color];
	}

}

void red_delay() {
	_delay_ms(500);
}