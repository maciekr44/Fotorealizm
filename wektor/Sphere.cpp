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

IntersectionResult Sphere::Hit(Ray ray, float t_min, float t_max) const {
    IntersectionResult result;
    result.type = MISS;
    ray.Origin().sub(this->Center_);
    Vector oc = ray.Origin();
    float a = ray.getDirection().dotProduct(ray.getDirection());
    float b = oc.dotProduct(ray.getDirection());
    float c = oc.dotProduct(oc) - this->Radius_ * this->Radius_;
    float discriminant = b * b - a * c;

    if (discriminant > 0) {
        float temp = (-b - sqrtf(discriminant)) / a;
        if (temp < t_max && temp > t_min) {
            result.color = this->Color_;
            result.LPOINT =  ray.PointAtParameter(temp);
            cout << result.LPOINT.showCoordinates() << endl;
            result.type = HIT;
            Vector kc = result.LPOINT;
            kc.sub(ray.Origin());
            result.distance = kc.length();
            Vector otwor = result.LPOINT;
            otwor.sub(this->Center_);
            otwor.normalize();
            result.intersectionLPOINTNormal = otwor;
            return result;
        }
        temp = (-b + sqrtf(discriminant)) / a;
        if (temp < t_max && temp > t_min) {
            result.LPOINT =  ray.PointAtParameter(temp);
            cout << result.LPOINT.showCoordinates() << endl;
            result.type = HIT;
            Vector kc = result.LPOINT;
            kc.sub(ray.Origin());
            result.distance = kc.length();
            Vector otwor = result.LPOINT;
            otwor.sub(this->Center_);
            otwor.normalize();
            result.intersectionLPOINTNormal = otwor;
            return result;
        }
    }
    cout << "there no hit:" << endl;
//    return NULL;
    return result;
}

string Sphere::showCoordinates() const {
    return string("[(") + to_string(getCenter().getX()) + string(", ") + to_string(getCenter().getY()) + string(", ") + to_string(getCenter().getZ()) + string("), ") + to_string(getRadius()) + string("]");
}
