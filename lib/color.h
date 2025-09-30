#ifndef COLOR_H
#define COLOR_H
#define CONVERSION_FACTOR 255.999
#include "point.h"
#include <stdio.h>
#include "interval.h"
#include "math.h"

#define make_color make_point

typedef Point Color;

#define linear_to_gamma(x) x > 0 ? sqrt(x) : 0;

void write_color(FILE *output, Color *image, int N) {
	Interval clamper = make_interval(0, 0.999);
	for (int i = 0; i < N; i++) {
		Color p = image[i];
		p.x = linear_to_gamma(p.x);
		p.y = linear_to_gamma(p.y);
		p.z = linear_to_gamma(p.z);
		int red   = (int) (interval_clamp(clamper, p.x) * 256);
		int green = (int) (interval_clamp(clamper, p.y) * 256);
		int blue  = (int) (interval_clamp(clamper, p.z) * 256);
		fprintf(output, "%d %d %d\n", red, green, blue);
	}
}

#endif
