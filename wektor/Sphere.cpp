//
// Created by Maciek on 13.03.2024.
//

#include "Sphere.h"

Sphere::Sphere(Vector v, float r) : Center_(v), Radius_(r) {}

const Vector &Sphere::getCenter() const {
    return Center_;
}

void Sphere::setCenter(const Vector &center) {
    Center_ = center;
}

float Sphere::getRadius() const {
    return Radius_;
}

void Sphere::setRadius(float radius) {
    Radius_ = radius;
}

bool Sphere::Hit(Ray ray, float t_min, float t_max) const {
    return false;
}

