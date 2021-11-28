/*
	That's basically the main low-level function from https://github.com/DannyHavenith/ws2811

	(Related post: http://rurandom.org/justintime/index.php?title=Driving_the_WS2811_at_800_kHz_with_an_8_MHz_AVR)

	That's the most led control operation (sends an array of values over time).
	Notice that it's intented to work with an 8Mhz clocked micro
*/

struct ws2811_color { // order: green - red - blue
	uint8_t green;
	uint8_t red;
	uint8_t blue;
};

void ws2811_send(struct ws2811_color *values, int length, int port_addr_led) {

	uint8_t bitcount = 7;

	uint8_t low_val = PORTB & ~(1 << port_addr_led);
	uint8_t high_val = PORTB | (1 << port_addr_led);
	uint16_t size = length * 3; // size in bytes (rgb, 1 byte per color)

	__asm__ volatile(
			"start:  LDI %[bits], 7                          \n" // start code, load bit count
			"        LD __tmp_reg__, %a[dataptr]+            \n" // fetch first byte
			"cont06: NOP                                     \n"
			"cont07: NOP                                     \n"
			"        OUT %[portout], %[downreg]              \n" // Force line down, even if it already was down
			"cont09: LSL __tmp_reg__                         \n" // Load next bit into carry flag.
			"s00:    OUT %[portout], %[upreg]                \n" // Start of bit, bit value is in carry flag
			"        BRCS skip03                             \n" // only lower the line if the bit...
			"        OUT %[portout], %[downreg]              \n" // ...in the carry flag was zero.
			"skip03: SUBI %[bits], 1                         \n" // Decrease bit count...
			"        BRNE cont06                             \n" // ...and loop if not zero
			"        LSL __tmp_reg__                         \n" // Load the last bit into the carry flag
			"        BRCC Lx008                              \n" // Jump if last bit is zero
			"        LDI %[bits], 7                          \n" // Reset bit counter to 7
			"        OUT %[portout], %[downreg]              \n" // Force line down, even if it already was down
			"        NOP                                     \n"
			"        OUT %[portout], %[upreg]                \n" // Start of last bit of byte, which is 1
			"        SBIW %[bytes], 1                        \n" // Decrease byte count
			"        LD __tmp_reg__, %a[dataptr]+            \n" // Load next byte
			"        BRNE cont07                             \n" // Loop if byte count is not zero
			"        RJMP brk18                              \n" // Byte count is zero, jump to the end
			"Lx008:  OUT %[portout], %[downreg]              \n" // Last bit is zero
			"        LDI %[bits], 7                          \n" // Reset bit counter to 7
			"        OUT %[portout], %[upreg]                \n" // Start of last bit of byte, which is 0
			"        NOP                                     \n"
			"        OUT %[portout], %[downreg]              \n" // We know we're transmitting a 0
			"        SBIW %[bytes], 1                        \n" // Decrease byte count
			"        LD __tmp_reg__, %a[dataptr]+            \n"
			"        BRNE cont09                             \n" // Loop if byte count is not zero
			"brk18:  OUT %[portout], %[downreg]              \n"
			"                                                \n" // used to be a NOP here, but returning from the function takes long enough
			"                                                \n" // We're done.
		: /* no output */
		: /* inputs */
		[dataptr] "e" (values), 	// pointer to grb values
		[upreg]   "r" (high_val),	// register that contains the "up" value for the output port (constant)
		[downreg] "r" (low_val),	// register that contains the "down" value for the output port (constant)
		[bytes]   "w" (size),		// number of bytes to send
		[bits]    "d" (bitcount),       // number of bits/2
		[portout] "I" (_SFR_IO_ADDR(PORTB)) // The port to use
	);

}