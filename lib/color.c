#include "color.h"

extern Color linear_to_gamma(Color linear_col);

extern struct Binary_color color_to_binary(Color col);

void write_to_image(FILE *file, Color *image, int length) {
	for (int i = 0; i < length; i++) {
		Color corrected_color = linear_to_gamma(image[i]);
		struct Binary_color color_bin = color_to_binary(corrected_color);
		fputc(color_bin.red, file);
		fputc(color_bin.green, file);
		fputc(color_bin.blue, file);
	}	
}
