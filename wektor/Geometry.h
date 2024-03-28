#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "IntersectionResult.h"
//#include "Ray.h"
//#include "Plane.h"
//#include "Sphere.h"
//#include "Triangle.h"



class Geometry {
public:
    virtual ~Geometry() {}
    virtual IntersectionResult collision(Ray ray, float t_min, float t_max) const{};

};
#endif // GEOMETRY_H