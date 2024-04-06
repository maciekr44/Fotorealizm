//
// Created by Kiu on 28.03.2024.
//

#ifndef WEKTORY_POINTLIGHT_H
#define WEKTORY_POINTLIGHT_H

#include "LightSource.h"
#include "Vector.h"
#include "IntersectionResult.h"
#include "Geometry.h"

class PointLight: public LightSource {
public:
    Vector location;
    float constAtten;
    float linearAtten;
    float quadAtten;


    PointLight(Vector location, float constAtten, float linearAtten, float quadAtten);

    Intensity getDiffuse(Vector cameraPosition, IntersectionResult result);
    Intensity getSpecular(Vector cameraPosition, IntersectionResult result);
    int isInShadow(IntersectionResult iInfo, Geometry* object);
};


#endif //WEKTORY_POINTLIGHT_H
