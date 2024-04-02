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

    virtual Intensity getDiffuse(IntersectionResult result) override;
    virtual Intensity getSpecular(Vector cameraPosition, IntersectionResult result, float shininess) override;
    virtual bool isInShadow(IntersectionResult iInfo, Geometry *const *pGeometry) override;
};


#endif //WEKTORY_POINTLIGHT_H
