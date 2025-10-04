#ifndef RAY_H
#define RAY_H

#include "point.h"

struct Ray {Point origin; Vector direction;};
typedef struct Ray Ray;

inline Ray make_ray (Point origin, Vector direction) {
	return (Ray) {origin, direction};
}

inline Point point_at_ray (Ray ray, scalar t) {
	return add_points(ray.origin, scale_point(t, ray.direction));
} 

#endif
