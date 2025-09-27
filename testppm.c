#include <stdio.h>
#include "color.h"

int main() {
	int IMAGE_WIDTH = 256;
	int IMAGE_HEIGHT = 256;
	int MAX_COLOR = 255;

	printf("P3\n%d %d\n%d\n", IMAGE_WIDTH, IMAGE_HEIGHT, MAX_COLOR);

	for(int row = 0; row < IMAGE_HEIGHT; row++) {
		for(int column = 0; column < IMAGE_WIDTH; column++) {
			double red_content = (double) column / (IMAGE_WIDTH - 1);
			double green_content = (double) row / (IMAGE_HEIGHT - 1);
			Pixel *p = make_point(red_content, green_content, 0.0);
			write_color(stdout, p);
		}
	}
	return 0;
}
