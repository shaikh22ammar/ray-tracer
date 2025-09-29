#ifndef COLOR_H
#define COLOR_H
#define CONVERSION_FACTOR 255.999
#include "point.h"
#include <stdio.h>
#include "interval.h"

#define make_color make_point

typedef Point Color;


void write_color(FILE *output, Color p) {
	Interval clamper = make_interval(0, 0.999);
	int red   = (int) (interval_clamp(clamper, p.x) * 256);
	int green = (int) (interval_clamp(clamper, p.y) * 256);
	int blue  = (int) (interval_clamp(clamper, p.z) * 256);
	fprintf(output, "%d %d %d\n", red, green, blue);
}

#endif
