#ifndef SPHERE_H
#define SPHERE_H

#include "point.h"
#include "ray.h"
#include "hittable.h"
#include "interval.h"

struct Sphere {scalar radius; Point center;};
typedef struct Sphere Sphere;

Sphere make_sphere(scalar radius, Point center);
int ray_hits_sphere(Ray r, Interval t_limit, void *sphere_void, struct Hit_record *rec);
#endif
