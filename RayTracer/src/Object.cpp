#include "Object.h"


void Object::setMaterial(Material * mat){
    m = mat;   
}

Triangle::Triangle(Point v1,Point v2, Point v3, Point no){
    p1 = v1;
    p2 = v2;
    p3 = v3;
    
    n = no;
    isLight = false;
}

Sphere::Sphere(Point p, double r){
    center = p;
    radius = r;
    
    isLight = false;
}
#define EPS 1E-6

Point Triangle::getIntersection(Ray r){

	// YOUR INTERSECTION CODE HERE.
	// RETURN THE POINT OF INTERSECTION FOR THIS TRIANGLE.

    return Point::Infinite();
}

Point Triangle::getNormal(Point p){
    Point one = p1-p2;
    Point two = p1-p3;
    Point ret = one.cross(two);
    ret.normalize();
    return ret;
}

Point Sphere::getNormal(Point p){
    Point ret = (p-center);
    
    ret.normalize();
    return ret;
}

Point Sphere::getIntersection(Ray r){

	// YOUR INTERSECTION CODE HERE.
	// RETURN THE POINT OF INTERSECTION FOR THIS SPHERE.

	Point L = r.p - center;
	double a = 1;
	double b = 2 * (r.v * L);
	double c = (L * L) - (radius * radius);

	double discrm = (b * b) - (4 * a * c);

	double t;

	if (discrm < 0)
		return Point::Infinite();
	else if (discrm == 0) {
		t = -(b / (double)(2 * a));
	} else {
		t = (-b + sqrt(discrm)) / (double)(2 * a);
	}


	return r.p + (r.v * t);
}

