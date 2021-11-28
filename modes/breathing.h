#include <util/delay.h>

#define BREATHING_STEPS_HOLDING_MAX	 50

const uint8_t breathing_increment = 0x05;
const uint8_t breathing_min = 0x05;
const uint8_t breathing_max = 0xFA;

char breathing_direction = 1;

char breathing_hold = 0;
char breathing_steps_holding_current = 0;

void breathing_init() {

	breathing_direction = 1;
	breathing_hold = 0;
	breathing_steps_holding_current = 0;

	for (int i = 0; i < LEDS_LENGTH; i++) {
		led_strip[i] = colors[COLOR_EMPTY];

		if (current_color == COLOR_RED) {
			led_strip[i].red = breathing_increment;
		} else {
			led_strip[i].blue = breathing_increment;
		}
	}

}

void breathing_step() {

	if (breathing_hold) {
		return;
	}

	for (int i = 0; i < LEDS_LENGTH; i++) {
		if (current_color == COLOR_RED) {
			led_strip[i].red += breathing_increment * breathing_direction;
		} else {
			led_strip[i].blue += breathing_increment * breathing_direction;
		}
	}

	uint8_t projected_red = led_strip[0].red + breathing_increment * breathing_direction;
	uint8_t projected_blue = led_strip[0].blue + breathing_increment * breathing_direction;

	if (
		(current_color == COLOR_RED && (projected_red > breathing_max || projected_red < breathing_min)) || 
		(current_color == COLOR_BLUE && (projected_blue > breathing_max || projected_blue < breathing_min))
	) {
		breathing_direction *= -1;
		breathing_hold = 1;
	}

}

void breathing_delay() {
	if (breathing_hold && ++breathing_steps_holding_current >= BREATHING_STEPS_HOLDING_MAX) {
		breathing_hold = 0;
		breathing_steps_holding_current = 0;
	}

	// use small delays with cycle counters instead of big ones to be able to
	// handle interrupts between them. Otherwise the delay feels too weird

	_delay_ms(100);
}