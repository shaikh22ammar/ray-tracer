#include "point.h"
#include <math.h>

//struct Point {scalar x; scalar y; scalar z;};

Point make_point(scalar x, scalar y, scalar z) {
	Point p = {x,y,z};
	return p;
}

Point negative_point(Point p) {
	return make_point(-p.x, -p.y, -p.z);
}

Point add_points(Point p1, Point p2) {
	return make_point(
			p1.x + p2.x, 
			p1.y + p2.y, 
			p1.z + p2.z);
}

Point multiply_points(Point p, Point q) {
	return make_point(
			p.x * q.x,
			p.y * q.y,
			p.z * q.z);
}

Vector subtract_points(Point p1, Point p2) {
	return make_point(
			p1.x - p2.x, 
			p1.y - p2.y, 
			p1.z - p2.z);
}

Point cross_product(Point p, Point q) {
	return make_point(
			p.y * q.z - p.z * q.y,
			p.z * q.x - p.x * q.z,
			p.x * q.y - p.y * p.x);
}

scalar dot_product(Point p1, Point p2) {
	return p1.x * p2.x 
		 + p1.y * p2.y 
		 + p1.z * p2.z;
}

scalar norm(Point p) {
	return (scalar) sqrt(dot_product(p,p));
}

Point scale_point(scalar t, Point p) {
	return make_point(t * (p.x), 
			t * (p.y), 
			t * (p.z));
}

Point unit_point(Point p) {
	return scale_point(1.0/norm(p), p);
}

int is_close_to_zero(Point p) {
	return dot_product(p,p) < 1e-4;
}
