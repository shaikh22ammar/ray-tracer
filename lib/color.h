#ifndef COLOR_H
#define COLOR_H

#include "point.h"

#define make_color make_point

typedef Point Color;
void write_color(FILE *output, Color *image, int N);

#endif
