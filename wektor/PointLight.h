//
// Created by Kiu on 28.03.2024.
//

#ifndef WEKTORY_POINTLIGHT_H
#define WEKTORY_POINTLIGHT_H

#include "Vector.h"
#include "Intensity.h"
//#include "IntersectionResult.h"

class PointLight{
public:

    Vector location;
    float constAtten;
    float linearAtten;
    Intensity color;

    PointLight();
    PointLight(Vector location, float constAtten, float linearAtten, Intensity color);

};


#endif //WEKTORY_POINTLIGHT_H
