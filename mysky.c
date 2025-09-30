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

int main() {
	// hittable world list
	struct Hittable_list *world = NULL; 
	Sphere red_ball_1 = make_sphere(0.5, make_point(0,0,-1));
	Sphere ground_1 = make_sphere(100, make_point(0,-100.5,-1));
	struct Hittable red_ball = {&red_ball_1, &ray_hits_sphere};
	struct Hittable ground = {&ground_1, &ray_hits_sphere};
	insert_hittable_to_list(&world, red_ball);
	insert_hittable_to_list(&world, ground);

	// render
	output_file = fopen("mysky.ppm", "w");
	log_file = stderr;
	//log_file = fopen("mysky.log", "w");

	struct Camera *cam = (struct Camera *) malloc (sizeof(struct Camera));
	make_camera_defaults(cam, 400, (scalar) 16.0/9.0);
	render_camera(cam, world);

	free(cam -> image);
	free(cam);
	fclose(log_file);
	fclose(output_file);
	return 0;
}
