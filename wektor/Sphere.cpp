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

Vector Ray::PointAtParameter(float t) {
    Direction_.mag(t);
    Origin_.add(Direction_);
    return Origin_;
}

Vector Sphere::Hit(Ray ray, float t_min, float t_max) const {
    ray.Origin().sub(this->Center_);
    Vector oc = ray.Origin();
    float a = ray.getDirection().dotProduct(ray.getDirection());
    float b = oc.dotProduct(ray.getDirection());
    float c = oc.dotProduct(oc) - this->Radius_ * this->Radius_;
    float discriminant = b * b - a * c;

    if (discriminant > 0) {
        float temp = (-b - sqrtf(discriminant)) / a;
        if (temp < t_max && temp > t_min) {
            Vector hit_point = ray.PointAtParameter(temp);
//            Vector normal = hit_point;
//            normal.sub(this->Center_);
//            normal.div(this->Radius_);
            cout << hit_point.showCoordinates() << endl;
            return hit_point;
        }
        temp = (-b + sqrtf(discriminant)) / a;
        if (temp < t_max && temp > t_min) {
            Vector hit_point = ray.PointAtParameter(temp);
//            Vector normal = hit_point;
//            normal.sub(this->Center_);
//            normal.div(this->Radius_);
            cout << hit_point.showCoordinates() << endl;
            return hit_point;
        }
    }
    cout << "there no hit:" << endl;
//    return NULL;
    return Vector(0,0,0);
}

string Sphere::showCoordinates() const {
    return string("[(") + to_string(getCenter().getX()) + string(", ") + to_string(getCenter().getY()) + string(", ") + to_string(getCenter().getZ()) + string("), ") + to_string(getRadius()) + string("]");
}

//std::pair<bool, std::pair<Vector, Vector>> checkIntersection(const Ray& ray, Sphere sphere) {
//    std::pair<bool, std::pair<Vector, Vector>> result;
//    result = sphere.Hit(ray, 0.001, 1000);
//    if (result.first) {
//        cout << "Kolizja!" << endl;
//        Vector normal = result.second.first; // Normalna w miejscu kolizji
//        Vector hit_point = result.second.second; // Punkt kolizji
//        cout << hit_point.showCoordinates() << endl;
//        // Możesz wykorzystać normalną i punkt kolizji do dalszych operacji, na przykład rysowania efektu kolizji
//    } else {
//        cout << "Brak kolizji." << endl;
//    }
//    cout << endl;
//}



