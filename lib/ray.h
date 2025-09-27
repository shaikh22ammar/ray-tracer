#ifndef RAY_H
#define RAY_H
#include "point.h"

struct Ray {Point origin; Vector direction;};
typedef struct Ray Ray;

Ray make_ray(Point origin, Vector direction);
Point point_at_ray(Ray ray, scalar t);

#endif
