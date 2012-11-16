/**
 * SPI Routines
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

#include <avr/io.h>

#include <stdint.h>

#include "spi.h"

void spi_init(void) {
	/* enable pins */
	SPI_DDR |= (1 << SPI_MOSI) | (1 << SPI_SCK) | (1 << SPI_SS);
	SPI_PORT |= (1 << SPI_SS);

	SPCR = 0;
	SPCR |= (1 << SPE);	/* SPI enable */
	SPCR |= (1 << SPIE);	/* SPI interrupt enable */
	SPCR |= (1 << MSTR);	/* SPI mode */

	/* set SPI rate */
	SPSR |= (1 << SPI2X);	/* double speed (F_CPU / 2) */
}

void spi_send(uint8_t byte) {
	SPDR = byte; /* start transmission */
	while (!(SPSR & (1 << SPIF))); /* wait for transmission complete */
}

void spi_sends(uint8_t *data, uint8_t len) {
	for (uint8_t i = 0; i < len; i++) {
		SPDR = data[i]; /* start transmission */
		while (!(SPSR & (1 << SPIF))); /* wait for transmission complete */
	}
}
