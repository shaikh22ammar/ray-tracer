#ifndef POINT_H
#define POINT_H

#include <math.h>
#include <float.h>

typedef float scalar;
#define SCALAR_MAX FLT_MAX

struct Point {scalar x; scalar y; scalar z;};
typedef struct Point Point;
typedef Point Vector;

inline Point make_point(scalar x, scalar y, scalar z) {
	return (Point) {x,y,z};
}

inline Point negative_point(Point p) {
	return (Point) {-p.x, -p.y, -p.z};
}

inline Point add_points(Point p, Point q) {
	return (Point) {
			p.x + q.x, 
			p.y + q.y, 
			p.z + q.z};
}

inline Point multiply_points(Point p, Point q) {
	return (Point) {
			p.x * q.x,
			p.y * q.y,
			p.z * q.z};
}

inline Vector subtract_points(Point p, Point q) {
	return (Point) {
			p.x - q.x, 
			p.y - q.y, 
			p.z - q.z};
}

inline Point cross_product(Point p, Point q) {
	return (Point) {
			p.y * q.z - p.z * q.y,
			p.z * q.x - p.x * q.z,
			p.x * q.y - p.y * p.x};
}

inline scalar dot_product(Point p, Point q) {
	return p.x * q.x 
		 + p.y * q.y 
		 + p.z * q.z;
}

inline scalar norm(Point p) {
	return (scalar) sqrt(dot_product(p,p));
}

inline Point scale_point(scalar t, Point p) {
	return (Point) {
			t * (p.x), 
			t * (p.y), 
			t * (p.z)};
}

inline Point unit_point(Point p) {
	return scale_point(1.0/norm(p), p);
}

inline int point_is_close_to_zero(Point p) {
	return dot_product(p,p) < 1e-4;
}

#endif

//test
