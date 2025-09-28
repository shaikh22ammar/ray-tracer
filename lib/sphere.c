#include "sphere.h"
#include <math.h>


Sphere make_sphere(scalar radius, Point center) {
	Sphere C = {radius, center};
	return C;
}

int ray_hits_sphere(Ray r, Interval t_limit, void *sphere_void, struct Hit_record *rec) {
	scalar a, h, c; 
	Sphere C = *((Sphere *) sphere_void);
	a = dot_product(r.direction, r.direction);
	Point p = subtract_points(C.center, r.origin);
	h = dot_product(r.direction, p);
	c = dot_product(p,p) - C.radius*C.radius;
	scalar sqrt_discriminant = (h*h - a*c);
	if (sqrt_discriminant < 0)
		return 0;
	sqrt_discriminant = sqrt(sqrt_discriminant);
	scalar root = (h - sqrt_discriminant) / a;
	if (!interval_contains_strict(t_limit, root)) {
		root = (h + sqrt_discriminant) / a;
		if (!interval_contains_strict(t_limit, root))
			return 0;
	}
	rec -> ray_t = root;
	rec -> ray_hit_point = point_at_ray(r, root);
	rec -> normal = 
		scale_point(
			1.0/C.radius,
			subtract_points(rec->ray_hit_point, C.center));
	return 1;
}
