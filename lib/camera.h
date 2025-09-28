#ifndef CAMERA_H
#define CAMERA_H

#include "stdio.h"
#include "point.h"

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
	return cam;
}



struct Camera make_camera_defaults(int image_width, scalar aspect_ratio) {
	return make_camera(image_width, aspect_ratio, 1.0, 2.0, make_point(0,0,0));
}

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
	// fprintf(log_file, "Ray has hit nothing");
	Color blue = make_color(0.5, 0.7, 1.0);
	Color white = make_color(1, 1, 1);
	Vector unit_direction = unit_point(r.direction);
	scalar y_value = (unit_direction.y + 1.0)*0.5;
	return add_points(
			scale_point(1.0 - y_value, white),
			scale_point(y_value, blue));
}

void render_camera(struct Camera *cam, struct Hittable_list *world) {
	fprintf(output_file, "P3\n%d %d\n255\n", cam -> image_width, cam -> image_height);
	for(int i = 0; i < cam -> image_height; i++) {
		fprintf(log_file, "Scanline: %d\n", i);
		for(int j = 0; j < cam -> image_width; j++) {
			Point pixel_now = 
				add_points(
				add_points(
						cam -> pixel_00,
						scale_point(j, cam -> pixel_delta_h)),
						scale_point(i, cam -> pixel_delta_v));
			Ray r = make_ray(cam -> camera_center, subtract_points(pixel_now, cam -> camera_center));
			write_color(output_file, ray_color(r, world));
		}
	}
}

#endif
