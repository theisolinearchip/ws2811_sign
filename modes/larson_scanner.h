#include <util/delay.h>

int larson_scanner_current = 0;
char larson_scanner_direction = 1;

const static struct ws2811_color larson_scanner_colors[8] = {
	// red
	{ 0x00, 0x30, 0x00 },
	{ 0x00, 0x20, 0x00 },
	{ 0x00, 0x10, 0x00 },
	{ 0x00, 0x02, 0x00 },

	// blue
	{ 0x00, 0x00, 0x30 },
	{ 0x00, 0x00, 0x20 },
	{ 0x00, 0x00, 0x10 },
	{ 0x00, 0x00, 0x02 }
};

// using the main color as the "base", create four different "diffuse" variants
// in both directions by offseting the current position
struct ws2811_color larson_scanner_get_color(int i) {
	if (i == larson_scanner_current) {
		return colors[current_color];
	} else if (i - 1 == larson_scanner_current || i + 1 == larson_scanner_current) {
		return larson_scanner_colors[0 + (current_color == COLOR_RED ? 0 : 1) * 4];
	} else if (i - 2 == larson_scanner_current || i + 2 == larson_scanner_current) {
		return larson_scanner_colors[1 + (current_color == COLOR_RED ? 0 : 1) * 4];
	} else if (i - 3 == larson_scanner_current || i + 3 == larson_scanner_current) {
		return larson_scanner_colors[2 + (current_color == COLOR_RED ? 0 : 1) * 4];
	} else if (i - 4 == larson_scanner_current || i + 4 == larson_scanner_current) {
		return larson_scanner_colors[3 + (current_color == COLOR_RED ? 0 : 1) * 4];
	} else {
		return colors[COLOR_EMPTY];
	}
}

void larson_scanner_init() {

	larson_scanner_current = 0;

	for (int i = 0; i < LEDS_COLUMNS; i++) {
		set_column_color(i, larson_scanner_get_color(i));
	}

}

void larson_scanner_step() {

	for (int i = 0; i < LEDS_COLUMNS; i++) {
		set_column_color(i, larson_scanner_get_color(i));
	}

	if (
		larson_scanner_current + larson_scanner_direction >= LEDS_COLUMNS ||
		larson_scanner_current + larson_scanner_direction < 0
	) {
		larson_scanner_direction *= -1;
	}

	larson_scanner_current += larson_scanner_direction;

}

void larson_scanner_delay() {
	_delay_ms(80);
}

// --------------

// the double larson scanner works the same way but reaching only half the columns
// and then mirroring the same value to the other side (notice that the loop works
// until COLUMS/2 + 1 to add the last one that otherwise won't be reached with an
// odd number of columns - yup, then there'll be an overlapping with the middle
// column but that's okay)

void larson_scanner_double_init() {

	larson_scanner_current = 0;

	for (int i = 0; i < LEDS_COLUMNS/2 + 1; i++) {
		set_column_color(i, larson_scanner_get_color(i));
		set_column_color(LEDS_COLUMNS - i, larson_scanner_get_color(i));
	}

}

void larson_scanner_double_step() {

	for (int i = 0; i <= LEDS_COLUMNS/2 + 1; i++) {
		set_column_color(i, larson_scanner_get_color(i));
		set_column_color(LEDS_COLUMNS - i, larson_scanner_get_color(i));
	}

	if (
		larson_scanner_current + larson_scanner_direction >= LEDS_COLUMNS/2 ||
		larson_scanner_current + larson_scanner_direction < 0
	) {
		larson_scanner_direction *= -1;
	}

	larson_scanner_current += larson_scanner_direction;

}

void larson_scanner_double_delay() {
	_delay_ms(80);
}