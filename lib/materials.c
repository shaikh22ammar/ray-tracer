#include "materials.h"
#include <stdio.h>
#include <stdlib.h>
#include "random.h"
#include "math.h"

static int lambertian_scatter (struct Material *self, struct Hit_record *rec) {
	Vector scatter_direction = add_points(rec->normal, random_unit_vector());
	rec->scattered_ray = make_ray(rec->ray_hit_point, scatter_direction);
	rec->attenuation = self->albedo;
	return 1;	
}

static inline Ray ray_reflector (Ray r, Point hit_point, Vector normal) {
	Point a_v = subtract_points(r.origin, hit_point);
	return make_ray (
			hit_point, 
			subtract_points(
				scale_point(
					2.0*dot_product(a_v, normal), 
					normal),
				a_v)
			);
}

//static inline Vector reflection_direction (Vector in, Vector normal) {
//	return subtract_points (
//				in, 
//				scale_point(
//					2 * dot_product(in, normal), 
//					normal));
//}

static int mettalic_scatter (struct Material *self, struct Hit_record *rec) {
	scalar fuzziness = self->params[0];
	//Vector scatter_direction = unit_point(reflection_direction(rec->ray_hit_point, rec->normal));
	Ray reflected_ray = ray_reflector(rec->hit_ray, rec->ray_hit_point, rec->normal);
	reflected_ray.direction = unit_point(reflected_ray.direction);
	reflected_ray.direction = add_points(
			reflected_ray.direction,
			scale_point(fuzziness, random_unit_vector())
			);
	//scatter_direction = add_points(
	//		scatter_direction,
	//		scale_point(fuzziness, random_unit_vector()));
	//rec->scattered_ray = make_ray(rec->ray_hit_point, scatter_direction);
	rec->scattered_ray = reflected_ray;
	rec->attenuation = self->albedo;
	return (dot_product(rec->scattered_ray.direction, rec->normal) > 0);
}

static inline Vector refraction_direction (Vector in, Vector normal, scalar relative_refraction_coefficient) {
	scalar cos_theta = dot_product(in, normal);
	cos_theta = cos_theta > 1 ? 1 : cos_theta;
	Vector out_perp =  
		scale_point(
			relative_refraction_coefficient, 
			add_points(
				in,
				scale_point(
					cos_theta,
					normal)
				)
			);	
	Vector out_parallel = scale_point(
		sqrt(abs(1.0 - dot_product(out_perp, out_perp))),
		normal);
	return add_points(out_perp, out_parallel);
}

static int refractive_scatter (struct Material *self, struct Hit_record *rec) {
	Color attenuation = {1.0, 1.0, 1.0};
	relative_refraction_coefficient = self -> params[0];
	relative_refraction_coefficient = dot(rec -> normal, subtract_points(rec -> hit_ray.direction, rec -> hit_ray.origin)) > 0 ? 1.0/relative_refraction_coefficient : relative_refraction_coefficient;
}

struct Material *make_lambertian_material (Color albedo) {
	struct Material *lambertian = (struct Material *) malloc (sizeof(struct Material) );
	lambertian->albedo = albedo;
	lambertian->scatters = &lambertian_scatter;
	return lambertian;
}

struct Material *make_reflective_material (Color albedo, scalar fuzziness) {
	struct Material *metal = (struct Material *) malloc (sizeof(struct Material) + sizeof(scalar));
	metal->albedo = albedo;
	(metal->params)[0] = fuzziness;
	(metal->scatters) = &mettalic_scatter;
	return metal;
}
