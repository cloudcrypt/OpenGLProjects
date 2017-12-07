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
    return Point::Infinite();  
}

