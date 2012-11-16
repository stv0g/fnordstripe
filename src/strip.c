#include <avr/io.h>
#include <avr/interrupt.h>

#include "strip.h"

volatile dot_t dots[DOTS+2];

void strip_init(void) {
	for (uint8_t i = 0; i < DOTS+4; i++) {
		dots[i] = 0; /* all black */
	}

	strip_update(); /* trigger first update */
}

void strip_setdot(struct rgb_color rgb, uint8_t pos) {
	dots[pos] = strip_rgbtodot(rgb);
}

uint16_t strip_rgbtodot(struct rgb_color rgb) {
	uint8_t a = (1 << 7) | ((rgb.blue & 0xF8) >> 1) | ((rgb.red & 0xC0) >> 6);
	uint8_t b = ((rgb.red & 0x38) << 2) | ((rgb.green & 0xF8) >> 3);

	return a | (b << 8);
}

void strip_update(void) {
	static uint8_t pos = 0;
	static uint8_t sync = 4;

	if (sync) { /* send synchronisation */
		SPDR = 0x00;
		sync--;
	}
	else if (pos < sizeof(dots)) { /* send data */
		SPDR = *((uint8_t *) dots+pos);
		pos++;
	}
	else { /* update finished */
		pos = 0;
		sync = 4;
	}
}

ISR(SPI_STC_vect) {
	strip_update();
}
