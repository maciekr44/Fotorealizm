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
    ray.Origin().sub(this->Center_); //zapisuje sie w ray.Origin wynik sumy
    Vector oc = ray.Origin();
    float a = ray.getDirection().dotProduct(ray.getDirection());
    float b = oc.dotProduct(ray.getDirection());
    float c = oc.dotProduct(oc) - this->Radius_ * this->Radius_;
    float discriminant = b * b - a * c;

    if (discriminant > 0) {
        float temp = (-b - sqrtf(discriminant)) / a;
        if (temp < t_max && temp > t_min) {

            return true;
        }
        temp = (-b + sqrtf(discriminant)) / a;

        if (temp < t_max && temp > t_min) {
            return true;
        }
    }
    return false;
}

string Sphere::showCoordinates() const {
    return string("[(") + to_string(getCenter().getX()) + string(", ") + to_string(getCenter().getY()) + string(", ") + to_string(getCenter().getZ()) + string("), ") + to_string(getRadius()) + string("]");
}



