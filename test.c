#include <stdio.h>
#include <stdlib.h>
#include "lib/point.h"
#include "lib/color.h"

int main () {
	FILE *output = fopen("test.ppm", "w");
	FILE *log_f = fopen("test.log", "w");
	int W = 256, H = 256;
	fprintf(output, "P6\n%d %d\n255\n", W, H);
	Color *image = (Color *) malloc (sizeof(Color)*W*H);
	for (int i = 0; i < H; i++) {
		for(int j = 0; j < W; j++) {
			scalar red = (1.0*j) / (W - 1);
			scalar green = (1.0*i) / (H-1);
			scalar blue = 0.0;
			image[i*W + j] = (Color) {red, green, blue};
			fprintf(log_f, "%f %f\n", red, green);
		}
		fprintf(log_f, "\ni = %d", i + 1);
	}
	Color test_col = image[255*W + 0];
	fprintf(stderr, "\n%f %f",test_col.x, test_col.y);
	write_to_image(output, image, W*H);
	return 0;
}
