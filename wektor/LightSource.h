//
// Created by Kiu on 28.03.2024.
//

#ifndef LIGHTSOURCE_H
#define LIGHTSOURCE_H

#include "Intensity.h"
#include "Vector.h"
#include "IntersectionResult.h"
#include "Geometry.h"

class LightSource {
public:
    virtual Intensity getDiffuse(IntersectionResult result) = 0;
    virtual Intensity getSpecular(Vector cameraPosition, IntersectionResult result, float shininess) = 0;
    virtual bool isInShadow(IntersectionResult iInfo, Geometry *const *pGeometry) = 0;
};

#endif // LIGHTSOURCE_H