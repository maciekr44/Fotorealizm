//
// Created by Maciek on 13.03.2024.
//

#include "Sphere.h"
using namespace std;

Sphere::Sphere(Vector v, float r) : Center_(v), Radius_(r) {}

Sphere::~Sphere() {

}

Vector Sphere::getCenter() const {
    return Center_;
}

void Sphere::setCenter(Vector center) {
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

string Sphere::showCoordinates() const {
    return string("[(") + to_string(getCenter().getX()) + string(", ") + to_string(getCenter().getY()) + string(", ") + to_string(getCenter().getZ()) + string("), ") + to_string(getRadius()) + string("]");
}



