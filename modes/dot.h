#include <util/delay.h>

int dot_current = 0;
char dot_direction = 1;

void dot_init() {

	dot_current = 0;
	dot_direction = 1;

	led_strip[0] = colors[current_color];
	for (int i = 1; i < LEDS_LENGTH; i++) {
		led_strip[i] = colors[COLOR_EMPTY];;
	}

}

void dot_step() {
	
	for (int i = 0; i < LEDS_LENGTH; i++) {
		led_strip[i] = (i != dot_current ? colors[COLOR_EMPTY] : colors[current_color]);
	}

	if (
		dot_current + dot_direction >= LEDS_LENGTH ||
		dot_current + dot_direction < 0
	) {
		dot_direction *= -1;
	}

	dot_current += dot_direction;

}

void dot_delay() {
	_delay_ms(50);
}