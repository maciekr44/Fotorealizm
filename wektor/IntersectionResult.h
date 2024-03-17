//
// Created by Kiu on 17.03.2024.
//

#ifndef WEKTORY_INTERSECTIONRESULT_H
#define WEKTORY_INTERSECTIONRESULT_H

#endif //WEKTORY_INTERSECTIONRESULT_H

#include "Vector.h" // Assuming you have a Vector class defined
#include "Plane.h"
#include "Ray.h"

// Define enum for intersection type
enum IntersectionType {
    MISS,
    HIT,
    INSIDE_PRIMITIVE
};

// Define IntersectionResult class
class IntersectionResult {
public:
    IntersectionType type;
    Vector LPOINT; // Intersection point
    float distance; // Distance from ray origin to intersection point
    Vector intersectionLPOINTNormal; // Normal vector at the intersection point
//    IntersectionResult Intersects(const Ray &ray, float range) const;
};

