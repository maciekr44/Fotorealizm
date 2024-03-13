//
// Created by Maciek on 13.03.2024.
//

#include "Ray.h"

Ray::Ray(Vector origin, float dis) {

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

const Vector &Ray::getDirection() const {
    return Direction_;
}

void Ray::setDirection(const Vector &direction) {
    Direction_ = direction;
}

float Ray::getDistance() const {
    return Distance_;
}

void Ray::setDistance(float distance) {
    Distance_ = distance;
}



