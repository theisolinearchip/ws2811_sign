#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <avr/interrupt.h>

#include "ws2811_controller.h"
#include "led_strip_handler.h"


#define	PORT_LED		PB3
#define PORT_BUTTON		PB2 // also int0

volatile char mode_changed = 1; // set to 1 when changing mode (used to init the mode config)

// ------------------

ISR (INT0_vect) {
	if (!mode_changed) {
		mode_changed = 1;

		PORTB |= (1 << PORT_LED);

		if (++current_mode >= MODES) { // on modes_handler.h
			current_mode = 0;
		}
	}
}

int main(void) {

	DDRB |= (1 << PORT_LED);
	PORTB |= (1 << PORT_LED);

	DDRB |= (1 << PORT_ADDR_LEDS);
	PORTB |= (1 << PORT_ADDR_LEDS);

	// DDRB &= ~(1 << PORT_BUTTON); // it's already done by default when init
	PORTB |= (1 << PORT_BUTTON); // pull-up on button

	init_modes();
	
	GIMSK |= (1 << INT0);	// enable int0
	MCUCR |= (1 << ISC01);	// int when the signal goes to low - falling edge (aka "button pressed"), ISC01 = 1, ISC00 = 0 (default)
	sei();

	// check for the first button pressed (this will enable the BLUE COLOR)
	if (!(PINB & (1 << PORT_BUTTON))) {
		current_color = COLOR_BLUE;
	}

	// give some time for the led controllers to power up
	_delay_ms(200);

	while(1) {
		
		if (mode_changed) {
			exec_change_mode(current_mode);
			
			// debounce
			_delay_ms(500);

			mode_changed = 0;
			PORTB &= ~(1 << PORT_LED);
		}

		exec_mode_step();

		exec_update_leds();

		exec_mode_delay();

	}

}
