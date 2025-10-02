#include <stdio.h>
#include <stdlib.h>
#include "lib/point.h"
#include "lib/ray.h"
#include "lib/interval.h"
#include "lib/hittable.h"
#include "lib/hittable_list.h"
#include "lib/sphere.h"
#include "lib/camera.h"

FILE *log_file;
FILE *output_file;

int main(int argc, char *argv[]) {
	// hittable world list
	struct Hittable_list *world = NULL; 
	Sphere blue_ball_shape = make_sphere(0.5, make_point(0,0,-1.2));
	Sphere ground_shape = make_sphere(100, make_point(0,-100.5,-1));
	Sphere left_ball_shape = make_sphere(0.5, make_point(-1,0,-1));
	Sphere right_ball_shape = make_sphere(0.5, make_point(1,0,-1));

	struct Material ground_mat = {make_point(0.8, 0.8, 0.0), &lambertian_scatter};
	struct Material center_mat = {make_point(0.1, 0.2, 0.5), &lambertian_scatter};
	struct Material left_mat = {make_point(0.8, 0.8, 0.8), &reflective_scatter};
	struct Material right_mat = {make_point(0.8, 0.6, 0.2), &reflective_scatter};
	
	struct Hittable blue_ball = {&blue_ball_shape, &center_mat, &ray_hits_sphere};
	struct Hittable left_ball = {&left_ball_shape, &left_mat, &ray_hits_sphere};
	struct Hittable right_ball = {&right_ball_shape, &right_mat, &ray_hits_sphere};
	struct Hittable ground = {&ground_shape, &ground_mat, &ray_hits_sphere};

	insert_hittable_to_list(&world, blue_ball);
	insert_hittable_to_list(&world, left_ball);
	insert_hittable_to_list(&world, right_ball);
	insert_hittable_to_list(&world, ground);

	// render
	output_file = fopen("mysky.ppm", "w");
	log_file = stderr;
	//log_file = fopen("mysky.log", "w");
	
	int width = argc > 1 ? atoi(argv[1]) : 400;
	scalar aspect_ratio = argc > 3 ? ((scalar) atoi(argv[2])) / atoi(argv[3]) : (scalar) 16.0 / 9.0;
	int samples = argc > 4 ? atoi(argv[4]) : 100;

	struct Camera *cam = (struct Camera *) malloc (sizeof(struct Camera));
	make_camera_defaults(cam, width, aspect_ratio, samples);
	render_camera(cam, world);

	free(cam -> image);
	free(cam);
	fclose(log_file);
	fclose(output_file);
	return 0;
}
