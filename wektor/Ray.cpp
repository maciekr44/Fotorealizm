//
// Created by Maciek on 13.03.2024.
//

#include "Ray.h"
using namespace std;

Ray::Ray(Vector origin, Vector dis) {

}

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

float Ray::getDistance() const {
    return Distance_;
}

void Ray::setDistance(float distance) {
    Distance_ = distance;
}

string Ray::showCoordinates() const {
    return string("[(") + to_string(getOrigin().getX()) + string(", ") + to_string(getOrigin().getY()) + string(", ") + to_string(getOrigin().getZ()) +
    string("), (") + to_string(getDestination().getX()) + string(", ") + to_string(getDestination().getY()) + string(", ") + to_string(getDestination().getZ()) +
    string("),") +
    to_string(getDistance()) +  string("]");
}



