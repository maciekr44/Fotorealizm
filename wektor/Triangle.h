//
// Created by Kiu on 17.03.2024.
//

#ifndef WEKTORY_TRIANGLE_H
#define WEKTORY_TRIANGLE_H


#include "Geometry.h"
#include "Material.h"
//#include "IntersectionResult.h"

class Triangle : public Geometry{
public:
    Triangle(const Vector& vertex1, const Vector& vertex2, const Vector& vertex3, Material material);

    Vector vertices[3];
    Vector normals[3];

    const Vector &Vertex1_;
    const Vector &Vertex2_;
    const Vector &Vertex3_;
    Material Material_;

    IntersectionResult collision(Ray ray, float t_min, float t_max) const;

//    IntersectionResult collision(Ray ray, float t_min, float t_max, Vector A, Vector B, Vector C) const;
};

#endif //WEKTORY_TRIANGLE_H
