//
// Created by Kiu on 28.03.2024.
//

#ifndef WEKTORY_MATERIAL_H
#define WEKTORY_MATERIAL_H
#include "Intensity.h"
class Material{
public:
    Material();
    Material(const Intensity color, float specular, float shineness, float reflect);

    Intensity color;
    float specular;//[0,infinity]. 0 = matt
    float shineness;//(0, infinity). for phong lighting a.k.a shineness.
    float reflect; //[0,1]. 1 == total reflection, i.e. a perfect mirror
};

#endif //WEKTORY_MATERIAL_H