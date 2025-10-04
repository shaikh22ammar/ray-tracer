#ifndef HITTABLE_H
#define HITTABLE_H

#include "point.h"
#include "ray.h"
#include "color.h"

/* Hit_record is a data structure that contains results of a ray hitting a hittable. */
struct Hit_record{
	Ray hit_ray;
	Point ray_hit_point;
	Vector normal;
	scalar t;

	Ray scattered_ray;
	Color attenuation;
};

/* Hittable is a struct that models an object in the scene that can interact with a ray. */
struct Hittable {
	struct Shape *shape;
	struct Material *material;
};

/* Shape is a struct containing those properties of a hittable object that determine whether a ray hits it.
 * hits() is a function that determines whether where a ray hits it or not at t_min <= t <= t_max,
 * hit_record is updated with where the ray has hit and the normal at hit point. 
 * params[] is an integral array of relevant parameters that describe the shape. */
struct Shape {
	int (*hits)(struct Shape *self, Ray r, scalar t_min, scalar t_max, struct Hit_record *rec);
	scalar params[];
};

/* Material is a struct containing those properties of a hittable object that describe how a ray scatters after it has hit it.
 * albedo is the color of the material (i.e., what it reflects).
 * scatters() is a function that determines whether a ray that has hit it scatters or gets absorbed,
 * hit_record is updated with the scattered_rat. 
 * params[] is an integral array of relevant parameters that describe the material. */
struct Material {
	Color albedo;
	int (*scatters)(struct Material *self, struct Hit_record *rec);
	scalar params[];
};

/* An array of hittables */
struct Hittable_array {
	struct Hittable *first;
	int length;
};

/* This function iterates through an array of hittables,
 * finding the closest hittable that a ray hits,
 * returning 00, 01, 11 depending on whether the ray scatters, hits anything or not */
extern unsigned int ray_hits_array (struct Hittable_array world, Ray r, struct Hit_record *rec);

#endif
