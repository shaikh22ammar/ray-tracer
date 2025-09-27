#include <stdio.h>
#include "lib/point.h"
#include "lib/color.h"
#include "lib/ray.h"
#include "lib/sphere.h"

Color ray_color(Ray r) {
	Sphere C = make_sphere(0.5, make_point(0,0,-1));
	scalar t = ray_intersects_sphere(r, C);
	if (t > 0.0) {
		Point p = point_at_ray(r, t);
		p = subtract_points(p, make_point(0,0,-1));
		p = unit_point(p);
		return make_color(
				(p.x + 1.0)*0.5,
				(p.y + 1.0)*0.5,
				(p.z + 1.0)*0.5);
	}
	Color blue = make_point(0.5, 0.7, 1);
	Color white = make_point(1, 1, 1);
	Vector unit_r = unit_point(r.direction);
	scalar a = 0.5 * (unit_r.y + 1.0);
	return 
		add_points(
		scale_point(1.0 - a, white), 
		scale_point(a, blue)
		);
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

	// render
	printf("P3\n%d %d\n255\n", image_width, image_height);
	for(int i = 0; i < image_height; i++) {
		fprintf(stderr, "\rScanlines remaining %d", image_height - i);
		fflush(stderr);
		for(int j = 0; j < image_width; j++) {
			Point pixel_now = 
				add_points(
				add_points(
						pixel_00,
						scale_point(j, pixel_delta_h)),
						scale_point(i, pixel_delta_v));
			Ray r = make_ray(camera_center, subtract_points(pixel_now, camera_center));
			write_color(stdout, ray_color(r));
		}
	}
	return 0;
}
