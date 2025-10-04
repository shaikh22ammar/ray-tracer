#include <math.h>
#include "sphere.h"
#include <stdlib.h>

static int ray_hits_sphere (struct Shape *self, Ray r, scalar t_min, scalar t_max, struct Hit_record *rec) {
	scalar radius = (self->params)[0];
	Point center = {
 		(self->params)[1],
 		(self->params)[2],
 		(self->params)[3]};

	scalar a,h,c;
	a = dot_product(r.direction, r.direction);
	Point p = subtract_points(center, r.origin);
	h = dot_product(r.direction, p);
	c = dot_product(p,p) - radius*radius;
	scalar sqrt_discr = (h*h - a*c);
	if (sqrt_discr < 0)
		return 0;
	sqrt_discr = sqrt(sqrt_discr);
	scalar root = (h - sqrt_discr) / a;
	if (root <= t_min || root >= t_max) {
		root = (h + sqrt_discr) / a;
		if (root <= t_min || root >= t_max) {
			return 0;
		}
	}

	rec -> t = root;
	rec -> ray_hit_point = point_at_ray(r, root);
	rec -> normal =
		scale_point(
			1.0/radius,
			subtract_points(rec->ray_hit_point, center));
	return 1;
}

struct Shape *make_sphere_shape (scalar radius, Point center) {
	struct Shape *sphere = (struct Shape *) malloc (sizeof(struct Shape) + 4*sizeof(scalar));
	if (sphere == NULL)
		fprintf(stderr, "ERROR: Not enough memory to allocate sphere.");
	sphere->params[0] = radius;
	sphere->params[1] = center.x;
	sphere->params[2] = center.y;
	sphere->params[3] = center.z;
	sphere->hits = &ray_hits_sphere;
}
