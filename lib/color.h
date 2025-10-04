#ifndef COLOR_H
#define COLOR_H

#include "point.h"
#include "math.h"
#include <stdio.h>

typedef Point Color;
#define make_color make_point

struct Binary_color {
	unsigned char red : 8;
	unsigned char green: 8;
	unsigned char blue: 8;
};

inline Color linear_to_gamma(Color linear_col) {
	scalar gamma_inv = 0.45;

	if (linear_col.x < 0.018)
		linear_col.x *= 4.5;
	else 
		linear_col.x = 1.099 * pow(linear_col.x, gamma_inv) - 0.099;
	linear_col.x = linear_col.x < 0 ? 0 : linear_col.x;
	linear_col.x = linear_col.x > 1 ? 1 : linear_col.x;

	if (linear_col.y < 0.018)
		linear_col.y *= 4.5;
	else 
		linear_col.y = 1.099 * pow(linear_col.y, gamma_inv) - 0.099;
	linear_col.y = linear_col.y < 0 ? 0 : linear_col.y;
	linear_col.y = linear_col.y > 1 ? 1 : linear_col.y;

	if (linear_col.z < 0.018)
		linear_col.z *= 4.5;
	else 
		linear_col.z = 1.099 * pow(linear_col.z, gamma_inv) - 0.099;
	linear_col.z = linear_col.z < 0 ? 0 : linear_col.z;
	linear_col.z = linear_col.z > 1 ? 1 : linear_col.z;

	return linear_col;	
}

inline struct Binary_color color_to_binary(Color col) {
	col.x = col.x >= 1 ? 0.999 : col.x;
	col.y = col.y >= 1 ? 0.999 : col.y;
	col.z = col.z >= 1 ? 0.999 : col.z;

	struct Binary_color col_B = {0,0,0};

	col_B.red = (unsigned char) (256*col.x);
	col_B.green = (unsigned char) (256*col.y);
	col_B.blue = (unsigned char) (256*col.z);

	return col_B;
}

extern void write_to_image(FILE *file, Color *image, int length);

#endif
