#ifndef SPHERE_H
#define SPHERE_H

#include "point.h"
#include "ray.h"

struct Sphere {scalar radius; Point center;};
typedef struct Sphere Sphere;

Sphere make_sphere(scalar radius, Point center);
scalar ray_intersects_sphere(Ray r, Sphere C);

#endif
