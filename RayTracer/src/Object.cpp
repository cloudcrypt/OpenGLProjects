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

	Point p1p2 = p2 - p1;
	Point p1p3 = p3 - p1;
	Point pVec = r.v.cross(p1p3);
	float determinant = p1p2 * pVec;

	float kEpsilon = 1e-8;
	if (fabs(determinant) < kEpsilon)
		return Point::Infinite();

	float invDeterminant = 1 / determinant;
	
	Point tVec = r.p - p1;
	float u = (tVec * pVec) * invDeterminant;
	if (u < 0 || u > 1)
		return Point::Infinite();

	Point qVec = tVec.cross(p1p2);
	float v = (r.v * qVec) * invDeterminant;
	if (v < 0 || u + v > 1)
		return Point::Infinite();

	float t = (p1p3 * qVec) * invDeterminant;

	if (t < 0.0) {
		return Point::Infinite();
	}

    return r.p + (r.v * t);
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

	Point L = r.p - center;
	double a = 1;
	double b = 2 * (r.v * L);
	double c = (L * L) - (radius * radius);

	double discrm = (b * b) - (4 * a * c);

	double t;

	if (discrm < 0.0)
		return Point::Infinite();
	else if (discrm == 0) {
		t = -(b / (double)(2 * a));
	} else {
		double t0 = (-b + sqrt(discrm)) / (double)(2 * a);
		double t1 = (-b - sqrt(discrm)) / (double)(2 * a);
		if (t0 > t1) {
			double temp = t0;
			t0 = t1;
			t1 = temp;
		}
		if (t0 < 0) {
			if (t1 < 0) {
				return Point::Infinite();
			}
			else {
				t = t1;
			}
		}
		else {
			t = t0;
		}
	}


	return r.p + (r.v * t);
}

