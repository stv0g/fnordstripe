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

#include <stdint.h>

#include "color.h"

/**
 * convert hsv to rgb color
 * (see http://en.wikipedia.org/wiki/HSL_and_HSV#Conversion_from_HSV_to_RGB
 *  and http://www.enide.net/webcms/uploads/file/projects/powerpicrgb-irda/hsvspace.pdf)
 */
struct rgb_color hsv2rgb(struct hsv_color hsv) {
	struct rgb_color rgb;

	if (hsv.saturation == 0) {
		rgb.red = hsv.value;
		rgb.green = hsv.value;
		rgb.blue = hsv.value;
	}
	else {
		hsv.hue %= 360;

		uint16_t f = ((hsv.hue % 60) * 255 + 30) / 60;
		uint16_t p = (hsv.value * (255 - hsv.saturation)+128)/255;
		uint16_t q = ((hsv.value * (255 - (hsv.saturation * f + 128)/255)) + 128) / 255;
		uint16_t t = (hsv.value * (255 - ((hsv.saturation * (255 - f)) / 255))) / 255;

		uint8_t i = hsv.hue / 60;

		switch (i) {
			case 0:
				rgb.red = hsv.value;
				rgb.green = t;
				rgb.blue = p;
				break;
			case 1:
				rgb.red = q;
				rgb.green = hsv.value;
				rgb.blue = p;
				break;
			case 2:
				rgb.red = p;
				rgb.green = hsv.value;
				rgb.blue = t;
				break;
			case 3:
				rgb.red = p;
				rgb.green = q;
				rgb.blue = hsv.value;
				break;
			case 4:
				rgb.red = t;
				rgb.green = p;
				rgb.blue = hsv.value;
				break;
			case 5:
				rgb.red = hsv.value;
				rgb.green = p;
				rgb.blue = q;
				break;
		}
	}

	return rgb;
}
