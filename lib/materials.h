#ifndef MATERIALS_H
#define MATERIALS_H

#include "hittable.h"

extern struct Material *make_lambertian_material (Color albedo);
extern struct Material *make_reflective_material (Color albedo, scalar fuzziness);

#endif
