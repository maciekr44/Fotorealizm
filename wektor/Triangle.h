//
// Created by Kiu on 17.03.2024.
//

#ifndef WEKTORY_TRIANGLE_H
#define WEKTORY_TRIANGLE_H


#include "Geometry.h"
#include "Vector.h"
#include "Ray.h"
//#include "IntersectionResult.h"

class Triangle : public Geometry{
public:
    Triangle();
    Triangle(const Vector& vertex1, const Vector& vertex2, const Vector& vertex3);
    Triangle(const Vector& vertex1, const Vector& vertex2, const Vector& vertex3,
             const Vector& normal1, const Vector& normal2, const Vector& normal3);

    Vector vertices[3];
    Vector normals[3];

    static bool IntersectTriangle(Ray ray, Vector A, Vector B, Vector C);
};

#endif //WEKTORY_TRIANGLE_H
