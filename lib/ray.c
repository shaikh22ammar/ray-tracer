#include "ray.h"

Ray make_ray(Point origin, Vector direction) {
	Ray r = {origin, direction};
	return r;
}
Point point_at_ray(Ray ray, scalar t) {
	return add_points(ray.origin, scale_point(t, ray.direction));
}
