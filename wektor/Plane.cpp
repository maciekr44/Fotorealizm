//
// Created by Maciek on 13.03.2024.
//

#include "Plane.h"
using namespace std;

Plane::Plane(Vector normal_vector, Vector point) : Normal_vector_(normal_vector), Point_(point) {}

const Vector &Plane::getNormalVector() const {
    return Normal_vector_;
}

void Plane::setNormalVector(const Vector &normalVector) {
    Normal_vector_ = normalVector;
}

const Vector &Plane::getPoint() const {
    return Point_;
}

void Plane::setPoint(const Vector &point) {
    Point_ = point;
}

string Plane::showCoordinates() const {
    return string("[(") + to_string(getNormalVector().getX()) + string(", ") + to_string(getNormalVector().getY()) + string(", ") + to_string(getNormalVector().getZ()) + string("), (") + to_string(getPoint().getX()) + string(", ") + to_string(getPoint().getY()) + string(", ") + to_string(getPoint().getZ()) + string(")") + string("]");
}



IntersectionResult Plane::Intersects(Ray ray, float range) const {
    IntersectionResult result;
    result.type = MISS;
    Vector siema = (this->Normal_vector_);
    cout << siema.showCoordinates()<< endl;
    Vector duopa = ray.getDirection();
    float ndotD = siema.dotProduct(duopa);
    cout << duopa.showCoordinates()<< endl;
    if(ndotD==0){
        return result;
    }
    float t;
    float distance = -siema.dotProduct(ray.Origin()); // Use the origin (0, 0, 0) as a point on the plane
    cout << to_string(distance)<< endl;
    t = (- distance - siema.dotProduct(ray.Origin()))/ndotD;      // z przodu miało byc jeszcze " - distance"
    if (t>0) {
        if (range == 0.0f || t < range) {
            if (siema.dotProduct(ray.getDirection()) < 0)
                result.type = HIT;
            else
                result.type = INSIDE_PRIMITIVE;
            ray.getDirection().mag(t);
            ray.Origin().add(ray.getDirection());
            result.LPOINT = ray.Origin();
            result.distance = t;
            result.intersectionLPOINTNormal = siema;
        }
    }
    return result;
}