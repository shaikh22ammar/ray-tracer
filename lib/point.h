#ifndef POINT3_H
#define POINT3_H

#include <stdio.h>
#include <float.h>

//typedef double scalar;
//#define SCALAR_MAX DBL_MAX
typedef float scalar;
#define SCALAR_MAX FLT_MAX

struct Point {scalar x; scalar y; scalar z;};
typedef struct Point Point;
typedef Point Vector;

Point make_point(scalar x, scalar y, scalar z);
Point negative_point(Point p);
Point add_points(Point p1, Point p2);
Vector subtract_points(Point p1, Point p2);
Point cross_product(Point p, Point q);
scalar dot_product(Point p, Point q);
scalar norm(Point p);
Point scale_point(scalar t, Point p);
Point unit_point(Point p);

#endif
