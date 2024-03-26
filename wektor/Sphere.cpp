//
// Created by Maciek on 13.03.2024.
//

#include "Sphere.h"

using namespace std;

Sphere::Sphere(Vector v, float r, Intensity color) : Center_(v), Radius_(r), Color_(color) {}

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

Vector Ray::PointAtParameter(float t) {
    Direction_.mag(t);
    Origin_.add(Direction_);
    return Origin_;
}

#include "PerspectiveCamera.h"
IntersectionResult Sphere::Hit(Ray ray, float t_min, float t_max) const {
    IntersectionResult result;
    result.type = MISS;

    // Translate ray origin to the sphere's local coordinate system
    Vector origin = ray.getOrigin();
    origin.sub(Center_);
    Vector oc =  origin;

    // Calculate coefficients of the quadratic equation (a*t^2 + b*t + c = 0)
    float a = ray.getDirection().dotProduct(ray.getDirection());
    float b = 2.0f * oc.dotProduct(ray.getDirection());
    float c = oc.dotProduct(oc) - Radius_ * Radius_;

    // Calculate the discriminant to determine the number of intersections
    float discriminant = b * b - 4 * a * c;

    if (discriminant > 0) {
        // Calculate the solutions for t
        float t1 = (-b - sqrt(discriminant)) / (2.0f * a);
        float t2 = (-b + sqrt(discriminant)) / (2.0f * a);

        // Check if the solutions are within the valid range
        if (t1 > t_min && t1 < t_max) {
            // Update intersection result
            result.type = HIT;
            result.distance = t1;
            result.LPOINT = ray.PointAtParameter(t1);
            Vector intersPoint = result.LPOINT;
            intersPoint.sub(Center_);
            intersPoint.normalize();
            result.intersectionLPOINTNormal = intersPoint;
            result.color = Color_;
            return result;
        }
        if (t2 > t_min && t2 < t_max) {
            // Update intersection result
            result.type = HIT;
            result.distance = t2;
            result.LPOINT = ray.PointAtParameter(t2);
            Vector intersPoint = result.LPOINT;
            intersPoint.sub(Center_);
            intersPoint.normalize();
            result.intersectionLPOINTNormal = intersPoint;
            result.color = Color_;
            return result;
        }
    }

    return result;
}

string Sphere::showCoordinates() const {
    return string("[(") + to_string(getCenter().getX()) + string(", ") + to_string(getCenter().getY()) + string(", ") + to_string(getCenter().getZ()) + string("), ") + to_string(getRadius()) + string("]");
}

Intensity Sphere::getColor() {
    return Color_;
}

void Sphere::setColor(Intensity color) {

}
