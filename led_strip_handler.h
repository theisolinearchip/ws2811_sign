#include <avr/pgmspace.h> 

#define MODES 						6
#define MODES_FUNCTIONS_PER_MODE 	3

#define MODES_FUNCTION_SIZE 		MODES * MODES_FUNCTIONS_PER_MODE

#define	PORT_ADDR_LEDS				PB4
#define LEDS_LENGTH					71

#define COLOR_EMPTY 				0
#define COLOR_RED 					1
#define COLOR_BLUE	 				2

// general led strip
struct ws2811_color led_strip[LEDS_LENGTH];

// base colors
const static struct ws2811_color colors[3] = {
	{ 0x00, 0x00, 0x00 }, // empty
	{ 0x00, 0xFF, 0x00 }, // red
	{ 0x00, 0x00, 0xFF } // blue
};

int current_color = COLOR_RED;

// mode selector (start with this mode)
volatile char current_mode = 0;

// columns (used by the larson scanner)
#include "led_strip_columns.h"

void (*mode_init)();
void (*mode_step)();
void (*mode_delay)();

// MODES
#include "modes/single.h"
#include "modes/breathing.h"
#include "modes/dot.h"
#include "modes/larson_scanner.h"
#include "modes/glitched.h"

void (*modes_function[MODES_FUNCTION_SIZE])() = {
	red_init, red_step, red_delay,
	breathing_init, breathing_step, breathing_delay,
	larson_scanner_init, larson_scanner_step, larson_scanner_delay,
	larson_scanner_double_init, larson_scanner_double_step, larson_scanner_double_delay,
	glitched_init, glitched_step, glitched_delay,
	dot_init, dot_step, dot_delay
};

void init_modes() {
	mode_init = modes_function[0];
	mode_step = modes_function[1];
	mode_delay = modes_function[2];
}

void exec_change_mode(char new_mode) {	
	mode_init = modes_function[new_mode * MODES_FUNCTIONS_PER_MODE];
	mode_step = modes_function[new_mode * MODES_FUNCTIONS_PER_MODE + 1];
	mode_delay = modes_function[new_mode * MODES_FUNCTIONS_PER_MODE + 2];

	(*mode_init)();
}

void exec_mode_step() {
	(*mode_step)();
}

void exec_mode_delay() {
	(*mode_delay)();
}

void exec_update_leds() {
	ws2811_send(led_strip, LEDS_LENGTH, PORT_ADDR_LEDS);
}