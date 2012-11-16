/**
 * SPI routines
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

#ifndef _SPI_H_
#define _SPI_H_

#define SPI_DDR		DDRB
#define SPI_PORT	PORTB

#define SPI_MOSI	PB5
#define SPI_SCK		PB7
#define SPI_SS		PB4

void spi_init(void);
void spi_send(uint8_t byte);
void spi_sends(uint8_t *data, uint8_t len);

#endif /* _SPI_H_ */
