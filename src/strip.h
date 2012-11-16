#ifndef _STRIP_H_
#define _STRIP_H_

#include "color.h"

#define DOTS 50

typedef uint16_t dot_t;

void strip_init(void);
void strip_update(void);
void strip_setdot(struct rgb_color rgb, uint8_t pos);
uint16_t strip_rgbtodot(struct rgb_color rgb);

#endif /* _STRIP_H_ */
