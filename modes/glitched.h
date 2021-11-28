#include <util/delay.h>

#define GLITCHED_STEPS_REGULAR_MAX_1	1		// regular blinking
#define GLITCHED_STEPS_REGULAR_MAX_2	2
#define GLITCHED_STEPS_LETTER_1_MAX_1	50		// letter 1 off
#define GLITCHED_STEPS_LETTER_1_MAX_2	55
#define GLITCHED_STEPS_LETTER_2_MAX_1	208		// letter 2 off
#define GLITCHED_STEPS_LETTER_2_MAX_2	222 

int glitched_steps_regular = 0;
int glitched_steps_letter_1 = 0;
int glitched_steps_letter_2 = 0;

const uint8_t glitched_low = 0x77;

void glitched_init() {

	glitched_steps_regular = 0;
	glitched_steps_letter_1 = 0;
	glitched_steps_letter_2 = 0;

	for (int i = 0; i < LEDS_LENGTH; i++) {
		led_strip[i] = colors[current_color];
	}

}

void glitched_step() {

	struct ws2811_color step_color = colors[current_color];
	if (glitched_steps_regular <= GLITCHED_STEPS_REGULAR_MAX_1) {
		step_color.green = 0x00;
		if (current_color == COLOR_RED) {
			step_color.red = glitched_low;
		} else {
			step_color.blue = glitched_low;
		}
	}
	
	for (int i = 0; i < LEDS_LENGTH; i++) {
		led_strip[i] = step_color;
	}

	if (glitched_steps_letter_1 <= GLITCHED_STEPS_LETTER_1_MAX_1) {
		set_column_color(0, step_color);
		set_column_color(1, step_color);
		set_column_color(2, step_color);
		set_column_color(3, step_color);
	} else {
		set_column_color(0, colors[COLOR_EMPTY]);
		set_column_color(1, colors[COLOR_EMPTY]);
		set_column_color(2, colors[COLOR_EMPTY]);
		set_column_color(3, colors[COLOR_EMPTY]);
	}

	if (glitched_steps_letter_2 <= GLITCHED_STEPS_LETTER_2_MAX_1) {
		set_column_color(16, step_color);
		set_column_color(17, step_color);
		set_column_color(18, step_color);
		set_column_color(19, step_color);
	} else {
		set_column_color(16, colors[COLOR_EMPTY]);
		set_column_color(17, colors[COLOR_EMPTY]);
		set_column_color(18, colors[COLOR_EMPTY]);
		set_column_color(19, colors[COLOR_EMPTY]);
	}
}

void glitched_delay() {
	if (++glitched_steps_regular > GLITCHED_STEPS_REGULAR_MAX_2) {
		glitched_steps_regular = 0;
	}
	if (++glitched_steps_letter_1 > GLITCHED_STEPS_LETTER_1_MAX_2) {
		glitched_steps_letter_1 = 0;
	}
	if (++glitched_steps_letter_2 > GLITCHED_STEPS_LETTER_2_MAX_2) {
		glitched_steps_letter_2 = 0;
	}
	

	_delay_ms(50);
}