//
// Created by Maciek on 13.03.2024.
//

#include "Sphere.h"

Sphere::Sphere() {
}

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
