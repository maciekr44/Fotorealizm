//
// Created by Kiu on 28.03.2024.
//

#ifndef WEKTORY_POINTLIGHT_H
#define WEKTORY_POINTLIGHT_H

#include "Vector.h"
#include "Intensity.h"
#include "IntersectionResult.h"
//#include "Intensity.h"
//#include "Intensity.h"
//#include "IntersectionResult.h"

class PointLight{
public:

    Vector location;
    float constAtten;
    float linearAtten;
    float quadAtten;
    Intensity color;

    PointLight();
    PointLight( Vector location, float constAtten, float linearAtten, float quadAtten, Intensity color);

//    Intensity getDiffuse(Vector cameraPosition, IntersectionResult result);
//    Intensity getSpecular(Vector cameraPosition, IntersectionResult result);
//    int isInShadow(IntersectionResult iInfo, Geometry* object);
    Vector calculateIntensity(PointLight pointLight, Vector Op);
    Vector isInShadow(PointLight pointLight, Vector Op);
    Intensity calculatePhong(Vector cameraPosition, IntersectionResult result, PointLight light, bool inShadow, Ray raySampling);
};


#endif //WEKTORY_POINTLIGHT_H
