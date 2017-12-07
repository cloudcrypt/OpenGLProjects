#include "RayTracer.h"

RayTracer::RayTracer(Scene * s, int maxd, int sm){
  scene = s;
  maxdepth = maxd;
  samples = sm;
}

// This function determines the closest object that a ray intersects.
// The getIntersection() method is polymorphic. Please provide implementations
// for all the objects in your scene (see Object.h and Object.cpp).
Object * RayTracer::intersect(Ray r, Point &interPnt){
  scene->startIteration();
  Object * current = NULL;
  Object * minObject = NULL;
  Point inter;
  //Initialize min to infinite point;
  Point min = Point::Infinite();
  while((current = scene->getNextObject()) != NULL){
    inter = current->getIntersection(r);
    if((inter - r.p).length() > 1E-6){
      if((inter-r.p).length()  < (min-r.p).length()){
        min = inter;
        minObject = current;
      }
    }
  }
  interPnt = min;
  return minObject;
}

// Trace a ray recursively
Color RayTracer::trace(Ray r, int depth){
  Color rad=Color(0.2,0.2,0.2,1.0);
  
  Object *hitObj;
  Point interPnt;
  if ((hitObj = intersect(r, interPnt)) == NULL) {
	  return rad;
  }
  rad = Phong(hitObj->getNormal(interPnt), interPnt, r, hitObj->getMaterial(), hitObj);
  //for (Point &light : scene->lights) {
	 // Ray *shadowRay = new Ray(interPnt, light - interPnt);
	 // Object *current = NULL;
	 // scene->startIteration();
	 // Point inter;
	 // bool illuminated = true;
	 // /*while ((current = scene->getNextObject()) != NULL) {
		//  inter = current->getIntersection(*shadowRay);
		//  if ((inter.x == Point::Infinite().x) && (inter.y == Point::Infinite().y) && (inter.z == Point::Infinite().z)) {
		//	  continue;
		//  }
		//  if ((inter - shadowRay->p).length() < (light - shadowRay->p).length()) {
		//	  illuminated = false;
		//	  break;
		//  }
	 // }*/
	 // if (illuminated) {
		//  rad = hitObj->getMaterial()->diffuse;

	 // }
  //}
  // YOUR CODE FOR RECURSIVE RAY TRACING GOES HERE
  
  return rad;
}

// Local Phong illumination at a point.
Color RayTracer::Phong(Point normal,Point p, Ray r, Material * m, Object * o){
	Color lightColor = Color(1.0, 1.0, 1.0, 1.0);
	Color ret = Color(0.0, 0.0, 0.0, 0.0);

	double diffuseStrength = 0.5;
	double ambientStrength = 0.2;



	ret = ret + ((lightColor * m->ambient) * ambientStrength);
  
	for (Point &light : scene->lights) {
		Ray *shadowRay = new Ray(p, light - p);
		Object *current = NULL;
		scene->startIteration();
		Point inter;
		bool illuminated = true;
		//while ((current = scene->getNextObject()) != NULL) {
		//inter = current->getIntersection(*shadowRay);
		//if ((inter.x == Point::Infinite().x) && (inter.y == Point::Infinite().y) && (inter.z == Point::Infinite().z)) {
		//continue;
		//}
		//if ((inter - shadowRay->p).length() < (light - shadowRay->p).length()) {
		//illuminated = false;
		//break;
		//}
		//}
		if (illuminated) {
			Point lightDir = light - p;
			lightDir.normalize();
			double diff = max(normal * lightDir, 0.0);
			ret = ret + (((m->diffuse * diff) * lightColor) * diffuseStrength);
		}
	}
	// YOUR CODE HERE.
	// There is ambient lighting irrespective of shadow.
	// Specular-diffuse lighting only if the point is not in shadow


  
	// Remember, you need to account for all the light sources.
  
	return ret;
}


// This function generates point on the image plane and starts a trace 
// through them.
// Grid supersampling is also implemented.
Color RayTracer::calculate(int x, int y){
  Color c = Color(0.0,0.0,0.0,0.0);
  for(int i = 1; i <= samples; i++){
    for(int j = 1; j <= samples; j++){
      double one, two;
      // We subtract 0.5 so that the (u,v)-origin is at the
      //center of the image plane.
      one = double(x)-0.5+double(i)/double(samples);
      two = double(y)-0.5+double(j)/double(samples);
      Ray r = scene->makeRay(one,two);
      c = c+trace(r,0);
    }
  }
  c = c*(1.0/double(samples*samples));
  return c;
}

