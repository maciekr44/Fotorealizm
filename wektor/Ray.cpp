//
// Created by Maciek on 13.03.2024.
//
#include <cmath>
#include "Ray.h"

using namespace std;

Ray::Ray(Vector origin, Vector destination) : Origin_(origin), Destination_(destination) {}

const Vector &Ray::getOrigin() const {
    return Origin_;
}

void Ray::setOrigin(const Vector &origin) {
    Origin_ = origin;
}

const Vector &Ray::getDestination() const {
    return Destination_;
}

void Ray::setDestination(const Vector &destination) {
    Destination_ = destination;
}

float Ray::getDistance() {
    float DistanceX = Destination_.getX() - Origin_.getX();
    float DistanceY = Destination_.getY() - Origin_.getY();
    float DistanceZ = Destination_.getZ() - Origin_.getZ();

    float distance_squared = DistanceX * DistanceX + DistanceY * DistanceY + DistanceZ * DistanceZ;
    return sqrt(distance_squared);
}

void Ray::setDistance(float distance) {
    Distance_ = distance;
}

string Ray::showCoordinates() {
    return string("[(") + to_string(Origin_.getX()) + string(", ") + to_string(Origin_.getY()) + string(", ") + to_string(Origin_.getZ()) +
           string("), (") + to_string(Destination_.getX()) + string(", ") + to_string(Destination_.getY()) + string(", ") + to_string(Destination_.getZ()) +
           string("), ") + to_string(getDistance()) +  string("]");
}


