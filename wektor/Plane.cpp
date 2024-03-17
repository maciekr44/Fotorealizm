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