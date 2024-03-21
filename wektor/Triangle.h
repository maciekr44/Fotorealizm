//
// Created by Kiu on 17.03.2024.
//

#ifndef WEKTORY_TRIANGLE_H
#define WEKTORY_TRIANGLE_H


#include "Vector.h"
#include "Ray.h"
#include "Geometry.h"
//#include "IntersectionResult.h"

class Triangle : Geometry{
public:
//    Triangle();
    Triangle(const Vector& vertex1, const Vector& vertex2, const Vector& vertex3, Intensity color);
//    Triangle(const Vector& vertex1, const Vector& vertex2, const Vector& vertex3,
//             const Vector& normal1, const Vector& normal2, const Vector& normal3);

    Vector vertices[3];
    Vector normals[3];

    IntersectionResult IntersectTriangle(Ray ray, Vector A, Vector B, Vector C);

    const Vector &Vertex1_;
    const Vector &Vertex2_;
    const Vector &Vertex3_;
    Intensity Color_;
};

#endif //WEKTORY_TRIANGLE_H
