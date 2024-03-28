//
// Created by Kiu on 28.03.2024.
//

#include "PointLight.h"

int PointLight::read(FILE *fp) {
    return 0;
}

void PointLight::write(FILE *fp) {

}

Vector PointLight::getDiffuse(Vector cameraPosition, IntersectionResult result) {
    return Vector();
}

Vector PointLight::getSpecular(Vector cameraPosition, IntersectionResult result) {
    return Vector();
}

int PointLight::isInShadow(IntersectionResult iInfo, Geometry *object) {
    return 0;
}
