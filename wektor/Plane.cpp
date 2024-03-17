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

IntersectionResult Plane::Intersects(Ray& ray, float range) {
    IntersectionResult result;
    Vector original = ray.getOrigin();
    Vector normal = getNormalVector();
    Vector direction = ray.getDirection();
    Vector point = getPoint();
    result.type = MISS;

    float ndotD = normal.dotProduct(ray.getDirection());
    if(ndotD==0) {
        return result;
    }
    float t;
    original.sub(point);
    t = (-normal.dotProduct(original)) / ndotD;
    if(t>0) {
        if(range==0.0f || t<range) {
            cout <<endl;
            if(normal.dotProduct(direction) < 0) {
                result.type = HIT;
            }
            else
                result.type = INSIDE_PRIMITIVE;
            direction.mag(t);
            direction.add(original);
            result.LPOINT = direction;
            result.distance = t;
            result.intersectionLPOINTNormal = normal;
        }
    }
    return result;
}