#include "sphere.h"
#include <math.h>

//struct Sphere {scalar radius; Point center;};
//typedef struct Sphere Sphere;

Sphere make_sphere(scalar radius, Point center) {
	Sphere C = {radius, center};
	return C;
}

scalar ray_intersects_sphere(Ray r, Sphere C) {
	scalar a, b, c;
	a = dot_product(r.direction, r.direction);
	Point p = subtract_points(C.center, r.origin);
	b = -2.0 * dot_product(r.direction, p);
	c = dot_product(p,p) - C.radius*C.radius;
	scalar discriminant = b*b - 4.0*a*c;
	if (discriminant < 0)
		return -1.0;
	return (-b - sqrt(discriminant)) / (2.0 * a);
}

