/**
 * Main routine
 *
 * @copyright	2012 Steffen Vogel
 * @license	http://www.gnu.org/licenses/gpl.txt GNU Public License
 * @author	Steffen Vogel <post@steffenvogel.de>
 * @link	http://www.steffenvogel.de
 */
/*
 * This file is part of fnordstripe
 *
 * fnordstripe is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * fnordstripe is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with fnordstripe. If not, see <http://www.gnu.org/licenses/>.
 */

#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include <stdio.h>

#include "spi.h"
#include "strip.h"
#include "color.h"
#include "uart.h"

#define BAUDRATE 9600

void timer_init() {
	TCCR0B |= (1 << CS01) | (1 << CS00); /* F_CPU / 64 = 250kHz */
	TIMSK0 |= (1 << TOIE0);
}

/* ~ 1kHz */
ISR(TIMER0_OVF_vect ) {
	strip_update();
}

int main(void) {
	/* init serial interface */
	uart_init(UART_BAUD_SELECT(BAUDRATE, F_CPU)); 

	/* init spi interface */
	spi_init();

	/* initialize LEDs */
	strip_init();

	timer_init();

	/* enable interrupts */
	sei();

	/* motd */
	uart_puts_P("\r\n\r\nfnordstripe 0.1\r\n");

	struct hsv_color hsvd, hsv = {
		.hue = 70,
		.saturation = 0xff,
		.value = 0xff
	};

	enum mode { HUE, SAT, VAL } m = HUE;
	char buf[32];

	while (1) {
		uint16_t r = uart_getc();
		char c = r & 0xff;

		if (r & UART_NO_DATA) {
			hsv.hue++;
			hsv.hue %= 360;
			
			for (uint8_t i = 0; i < DOTS; i++) {
				hsvd = hsv;
				hsvd.hue += 7*i;
				hsvd.hue %= 360;

				cli();
				strip_setdot(hsv2rgb(hsvd), i);
				sei();
			}
			_delay_ms(500);
		}
		else if (r & 0xff00) {
			uart_puts_P("error\r\n");
		}
		else if ( c == 'h' ) m = HUE;
		else if ( c == 'v' ) m = VAL;
		else if ( c == 's' ) m = SAT;
		else if ( c >= '0' && c <= '9') {
			switch (m) {
				case HUE:
					hsv.hue = (c - '0') * 36;
					sprintf(buf, "ok, hue: %d\r\n", hsv.hue);
					break;
				case SAT:
					hsv.saturation = (c- '0') * 25;
					sprintf(buf, "ok, saturation: %d\r\n", hsv.saturation);
					break;
				case VAL:
					hsv.value = (c- '0') * 25;
					sprintf(buf, "ok, value: %d\r\n", hsv.value);
					break;
			}

			uart_puts(buf);
		}
		else {
			uart_putc(c);
		}
	}

	return 0;
}
