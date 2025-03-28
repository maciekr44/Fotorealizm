//
// Created by Kiu on 17.03.2024.
//

#ifndef WEKTORY_INTERSECTIONRESULT_H
#define WEKTORY_INTERSECTIONRESULT_H

//#include "Vector.h"
//#include "Plane.h"
//#include "Ray.h"
//#include "Intensity.h"
//#include "Material.h"
//#include "Sphere.h"
#include "Vector.h"
#include "Material.h"

enum IntersectionType {
    MISS,
    HIT,
    INSIDE_PRIMITIVE
};

// Define IntersectionResult class
class IntersectionResult {
    // Define enum for intersection type

    public:
//        Intensity color;
        Material material;
        IntersectionType type;
        Vector LPOINT; // Intersection point
        float distance; // Distance from ray origin to intersection point
        Vector intersectionLPOINTNormal; // Normal vector at the intersection point
    //    IntersectionResult Intersects(const Ray &ray, float range) const;
};

#endif // WEKTORY_INTERSECTIONRESULT_H