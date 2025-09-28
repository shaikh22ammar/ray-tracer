#include <stdio.h>
#include <stdlib.h>
#include "lib/point.h"
#include "lib/color.h"
#include "lib/ray.h"
#include "lib/interval.h"
#include "lib/hittable.h"
#include "lib/hittable_list.h"
#include "lib/sphere.h"

FILE *log_file;
FILE *output_file;

Color ray_color(Ray r, struct Hittable_list *world) {
	struct Hit_record rec;
	if (ray_hits_hittable_list(r, positive_interval, (void *) world, &rec)) {
		fprintf(log_file, "Ray has hit at (%f,%f,%f) with normal (%f,%f,%f)\n", 
				rec.ray_hit_point.x, 
				rec.ray_hit_point.y, 
				rec.ray_hit_point.z, 
				rec.normal.x, 
				rec.normal.y, 
				rec.normal.z);
		Color ray_color = scale_point(0.5, add_points(rec.normal, make_color(1,1,1)));
		fprintf(log_file, "Ray color is (%f,%f,%f)\n", 
				ray_color.x,
				ray_color.y,
				ray_color.z);
		return ray_color;
	}
	
	// sky
	Color blue = make_color(0.5, 0.7, 1.0);
	Color white = make_color(1, 1, 1);
	Vector unit_direction = unit_point(r.direction);
	scalar y_value = (unit_direction.y + 1.0)*0.5;
	return add_points(
			scale_point(1.0 - y_value, white),
			scale_point(y_value, blue));
}

Color ray_color_debug(Ray r, Sphere *C) {
	struct Hit_record rec;
	if (ray_hits_sphere(r, positive_interval, (void *) C, &rec)) {
		return scale_point(0.5, add_points(rec.normal, make_color(1,1,1)));
	}
	return make_color(0,0,0);
}

int main() {
	// Image
	scalar aspect_ratio = 16.0 / 9.0;
	int image_width 	= 400;
	int image_height 	= (int) 400 / aspect_ratio;
	image_height 		= image_height < 1 ? 1 : image_height;

	// camera
	scalar focal_length    = 1.0;
	scalar viewport_height = 2.0;
	scalar viewport_width  = viewport_height * (1.0*image_width)/image_height;
	Point camera_center    = make_point(0, 0, 0);

	// viewport
	Vector viewport_h 	 = make_point(viewport_width, 0, 0);
	Vector viewport_v 	 = make_point(0, -viewport_height, 0);
	Vector pixel_delta_h = scale_point(1.0/image_width, viewport_h);
	Vector pixel_delta_v = scale_point(1.0/image_height, viewport_v);

	// pixel coordinates
	Point viewport_upperleft =
		add_points(
		add_points(
		add_points(
			camera_center, 
			make_point(0, 0, -focal_length)),
			scale_point(-0.5, viewport_h)),
			scale_point(-0.5, viewport_v));
	Point pixel_00 = 
		add_points(
		add_points(
			viewport_upperleft,
			scale_point(0.5, pixel_delta_h)),
			scale_point(0.5, pixel_delta_v));

	// hittable world list
	struct Hittable_list *world = NULL; 
	Sphere red_ball_1 = make_sphere(0.5, make_point(0,0,-1));
	Sphere ground_1 = make_sphere(100, make_point(0,-100.5,-1));
	struct Hittable red_ball = {&red_ball_1, &ray_hits_sphere};
	struct Hittable ground = {&ground_1, &ray_hits_sphere};
	insert_hittable_to_list(&world, red_ball);
	insert_hittable_to_list(&world, ground);

	// render
	//FILE *output, *log;
	output_file = fopen("mysky.ppm", "w");
	log_file = fopen("mysky.log", "w");
	fprintf(output_file, "P3\n%d %d\n255\n", image_width, image_height);
	for(int i = 0; i < image_height; i++) {
		fprintf(log_file, "Scanline: %d\n", i);
		for(int j = 0; j < image_width; j++) {
			Point pixel_now = 
				add_points(
				add_points(
						pixel_00,
						scale_point(j, pixel_delta_h)),
						scale_point(i, pixel_delta_v));
			Ray r = make_ray(camera_center, subtract_points(pixel_now, camera_center));
/*			fprintf(log_file, "Ray : origin = (%f,%f,%f), direction = (%f,%f,%f)\n", 
					r.origin.x, 
					r.origin.y, 
					r.origin.z, 
					r.direction.x,
					r.direction.y,
					r.direction.z);*/
			write_color(output_file, ray_color(r, world));
		}
	}
	fclose(log_file);
	fclose(output_file);
	return 0;
}
