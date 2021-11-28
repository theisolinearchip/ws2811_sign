// separate definitions for columns

#define LEDS_COLUMNS 		24 // 24

#define LED_COLUMN_0_SIZE 	5
#define LED_COLUMN_1_SIZE 	3
#define LED_COLUMN_2_SIZE 	3
#define LED_COLUMN_3_SIZE 	2

#define LED_COLUMN_4_SIZE 	5
#define LED_COLUMN_5_SIZE 	1
#define LED_COLUMN_6_SIZE 	1
#define LED_COLUMN_7_SIZE 	2

#define LED_COLUMN_8_SIZE 	5
#define LED_COLUMN_9_SIZE 	2
#define LED_COLUMN_10_SIZE 	2
#define LED_COLUMN_11_SIZE 	1

#define LED_COLUMN_12_SIZE 	5
#define LED_COLUMN_13_SIZE 	1
#define LED_COLUMN_14_SIZE 	1
#define LED_COLUMN_15_SIZE 	6

#define LED_COLUMN_16_SIZE 	5
#define LED_COLUMN_17_SIZE 	1
#define LED_COLUMN_18_SIZE 	1
#define LED_COLUMN_19_SIZE 	5

#define LED_COLUMN_20_SIZE 	4
#define LED_COLUMN_21_SIZE 	3
#define LED_COLUMN_22_SIZE 	3
#define LED_COLUMN_23_SIZE 	4

/*
	Currently handling "EL FUNS" letters, with the following:

	- E: 13		- 13
	- L: 9		- 22
	- F: 10		- 32
	- U: 13 	- 45
	- N: 12		- 57
	- S: 14 	- 71

*/

// E
PROGMEM const int led_strip_column_0[LED_COLUMN_0_SIZE] = { 0, 1, 2, 3, 4};
PROGMEM const int led_strip_column_1[LED_COLUMN_1_SIZE] = { 5, 8, 10 };
PROGMEM const int led_strip_column_2[LED_COLUMN_2_SIZE] = { 6, 9, 11 };
PROGMEM const int led_strip_column_3[LED_COLUMN_3_SIZE] = { 7, 12 };

// L
PROGMEM const int led_strip_column_4[LED_COLUMN_4_SIZE] = { 13, 14, 15, 16, 17 };
PROGMEM const int led_strip_column_5[LED_COLUMN_5_SIZE] = { 18 };
PROGMEM const int led_strip_column_6[LED_COLUMN_6_SIZE] = { 19 };
PROGMEM const int led_strip_column_7[LED_COLUMN_7_SIZE] = { 20, 21 };

// F
PROGMEM const int led_strip_column_8[LED_COLUMN_8_SIZE] = { 22, 23, 24, 25, 26 };
PROGMEM const int led_strip_column_9[LED_COLUMN_9_SIZE] = { 27, 30 };
PROGMEM const int led_strip_column_10[LED_COLUMN_10_SIZE] = { 28, 31 };
PROGMEM const int led_strip_column_11[LED_COLUMN_11_SIZE] = { 29 };

// U
PROGMEM const int led_strip_column_12[LED_COLUMN_12_SIZE] = { 32, 33, 34, 35, 36 };
PROGMEM const int led_strip_column_13[LED_COLUMN_13_SIZE] = { 37 };
PROGMEM const int led_strip_column_14[LED_COLUMN_14_SIZE] = { 38 };
PROGMEM const int led_strip_column_15[LED_COLUMN_15_SIZE] = { 39, 40, 41, 42, 43, 44 };

// N
PROGMEM const int led_strip_column_16[LED_COLUMN_16_SIZE] = { 45, 46, 47, 48, 49 };
PROGMEM const int led_strip_column_17[LED_COLUMN_17_SIZE] = { 50 };
PROGMEM const int led_strip_column_18[LED_COLUMN_18_SIZE] = { 51 };
PROGMEM const int led_strip_column_19[LED_COLUMN_19_SIZE] = { 56, 55, 54, 53, 52 };

// S
PROGMEM const int led_strip_column_20[LED_COLUMN_20_SIZE] = { 57, 65, 66, 67 };
PROGMEM const int led_strip_column_21[LED_COLUMN_21_SIZE] = { 58, 64, 68 };
PROGMEM const int led_strip_column_22[LED_COLUMN_22_SIZE] = { 59, 63, 69 };
PROGMEM const int led_strip_column_23[LED_COLUMN_23_SIZE] = { 60, 61, 62, 70 };

PROGMEM const int* const led_columns[LEDS_COLUMNS] = {
	led_strip_column_0,
	led_strip_column_1,
	led_strip_column_2,
	led_strip_column_3,

	led_strip_column_4,
	led_strip_column_5,
	led_strip_column_6,
	led_strip_column_7,

	led_strip_column_8,
	led_strip_column_9,
	led_strip_column_10,
	led_strip_column_11,

	led_strip_column_12,
	led_strip_column_13,
	led_strip_column_14,
	led_strip_column_15,

	led_strip_column_16,
	led_strip_column_17,
	led_strip_column_18,
	led_strip_column_19,

	led_strip_column_20,
	led_strip_column_21,
	led_strip_column_22,
	led_strip_column_23,

};

PROGMEM const int led_columns_size[LEDS_COLUMNS] = {
	LED_COLUMN_0_SIZE,
	LED_COLUMN_1_SIZE,
	LED_COLUMN_2_SIZE,
	LED_COLUMN_3_SIZE,

	LED_COLUMN_4_SIZE,
	LED_COLUMN_5_SIZE,
	LED_COLUMN_6_SIZE,
	LED_COLUMN_7_SIZE,

	LED_COLUMN_8_SIZE,
	LED_COLUMN_9_SIZE,
	LED_COLUMN_10_SIZE,
	LED_COLUMN_11_SIZE,

 	LED_COLUMN_12_SIZE,
 	LED_COLUMN_13_SIZE,
 	LED_COLUMN_14_SIZE,
 	LED_COLUMN_15_SIZE,
 
 	LED_COLUMN_16_SIZE,
 	LED_COLUMN_17_SIZE,
 	LED_COLUMN_18_SIZE,
 	LED_COLUMN_19_SIZE,
 
 	LED_COLUMN_20_SIZE,
 	LED_COLUMN_21_SIZE,
 	LED_COLUMN_22_SIZE,
 	LED_COLUMN_23_SIZE
};

int *led_strip_column_ptr;

void set_column_color(int column, struct ws2811_color color) {
	for (int i = 0; i < pgm_read_byte(&led_columns_size[column]); i++) {
		// first access the led_strip_column pointer (it's a word)
		led_strip_column_ptr = (int *) pgm_read_word(&led_columns[column]);

		// then access the content in the position
		led_strip[pgm_read_byte(&led_strip_column_ptr[i])] = color;
	}
}