#ifndef CAMERA_H
#define CAMERA_H

#include "stdio.h"
#include "point.h"
#include "random.h"

extern FILE *log_file;
extern FILE *output_file;

struct Camera {
	// image
	int image_width;
	scalar aspect_ratio;
	int image_height;

	// camera
	scalar focal_length;
	scalar viewport_height;
	scalar viewport_width;
	Point camera_center;

	// viewport
	Vector viewport_h;
	Vector viewport_v;
	Vector pixel_delta_h;
	Vector pixel_delta_v;

	// pixel coordinates
	Point viewport_upperleft;
	Point pixel_00;

	int samples_per_pixel;
	scalar sample_scale;

	int max_reflection_depth;
};

struct Camera make_camera (int image_width, scalar aspect_ratio, scalar focal_length, scalar viewport_height, Point camera_center) {
	struct Camera cam;
	// image
	cam.image_width = image_width;
	cam.aspect_ratio = aspect_ratio;
	cam.image_height = image_width / aspect_ratio; 
	cam.image_height = (cam.image_height < 1) ? 1 : cam.image_height;
	
	// camera
	cam.focal_length = focal_length;
	cam.viewport_height = viewport_height;
	cam.viewport_width = viewport_height * (1.0 * cam.image_width) / cam.image_height;
	cam.camera_center = camera_center;

	// viewport
	cam.viewport_h = make_point(cam.viewport_width, 0, 0);
	cam.viewport_v = make_point(0, -viewport_height, 0);
	cam.pixel_delta_h = scale_point(1.0/cam.image_width, cam.viewport_h);
	cam.pixel_delta_v = scale_point(1.0/cam.image_height, cam.viewport_v);

	// pixel_coordinates
	cam.viewport_upperleft = 
		add_points(
		add_points(
		add_points(
			camera_center, 
			make_point(0, 0, -focal_length)),
			scale_point(-0.5, cam.viewport_h)),
			scale_point(-0.5, cam.viewport_v));

	cam.pixel_00 = 
		add_points(
		add_points(
			cam.viewport_upperleft,
			scale_point(0.5, cam.pixel_delta_h)),
			scale_point(0.5, cam.pixel_delta_v));

	cam.samples_per_pixel = 100;
	cam.sample_scale = 1.0 / cam.samples_per_pixel;
	cam.max_reflection_depth = 50;
	return cam;
}



struct Camera make_camera_defaults(int image_width, scalar aspect_ratio) {
	return make_camera(image_width, aspect_ratio, 1.0, 2.0, make_point(0,0,0));
}

Point sample_square() {
	return make_point(random_scalar() - 0.5, random_scalar() - 0.5, 0);
}

Ray get_ray(struct Camera *cam, int i, int j) {
	Point offset = sample_square();
	Point sampled_pixel =
		add_points(
		add_points(
			cam->pixel_00,
			scale_point(j + random_scalar() - 0.5, cam->pixel_delta_h)),
			scale_point(i + random_scalar() - 0.5, cam->pixel_delta_v));
	return make_ray(cam->camera_center, subtract_points(sampled_pixel, cam->camera_center));
}

Color ray_color(Ray r, struct Hittable_list *world, int depth) {
	if (depth <= 0) 
		return make_color(0,0,0);
	struct Hit_record rec;
	if (ray_hits_hittable_list(r, make_interval(0.001, SCALAR_MAX), (void *) world, &rec)) {
		Vector direction = add_points(rec.normal, random_unit_vector());
		return scale_point(0.5,	
				ray_color(
					make_ray(rec.ray_hit_point, direction), 
					world, depth - 1));
	}
	
	// sky
	// fprintf(log_file, "Ray has hit nothing");
	Color blue = make_color(0.5, 0.7, 1.0);
	Color white = make_color(1, 1, 1);
	Vector unit_direction = unit_point(r.direction);
	scalar y_value = (unit_direction.y + 1.0)*0.5;
	Color ray_col = 
	add_points(
		scale_point(1.0 - y_value, white),
		scale_point(y_value, blue));
	return ray_col;
}

void render_camera(struct Camera *cam, struct Hittable_list *world) {
	fprintf(output_file, "P3\n%d %d\n255\n", cam -> image_width, cam -> image_height);
	for(int i = 0; i < cam -> image_height; i++) {
		fprintf(log_file, "Scanline: %d\n", i);
		for(int j = 0; j < cam -> image_width; j++) {
			Color pixel_color = make_point(0,0,0);
			for (int sample = 0; sample < cam -> samples_per_pixel; sample++) {
				Ray r = get_ray(cam, i, j);
				pixel_color = add_points(pixel_color, ray_color(r, world, cam->max_reflection_depth));
			}
			write_color(output_file, scale_point(cam->sample_scale, pixel_color));
		}
	}
}

#endif
