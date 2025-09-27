#ifndef COLOR_H
#define COLOR_H
#define CONVERSION_FACTOR 255.999
#include "point.h"
#include <stdio.h>

#define make_color make_point

typedef Point Color;


void write_color(FILE *output, Color p) {
	int red   = (int) (p.x * CONVERSION_FACTOR);
	int green = (int) (p.y * CONVERSION_FACTOR);
	int blue  = (int) (p.z * CONVERSION_FACTOR);
	fprintf(output, "%d %d %d\n", red, green, blue);
}

#endif
