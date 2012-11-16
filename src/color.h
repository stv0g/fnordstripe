/**
 * Color types & conversion
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

#ifndef _COLOR_H_
#define _COLOR_H_

#include <stdint.h>

struct rgb_color {
	uint8_t blue;
	uint8_t green;
	uint8_t red;
};

struct hsv_color {
	uint16_t hue;
	uint8_t saturation;
	uint8_t value;
};

struct rgb_color hsv2rgb(struct hsv_color hsv);

#endif /* _COLOR_H_ */
