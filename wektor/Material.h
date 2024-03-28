//
// Created by Kiu on 28.03.2024.
//

#ifndef WEKTORY_MATERIAL_H
#define WEKTORY_MATERIAL_H
#include "Intensity.h"
class Material{
public:
    Material();
    Material(const Intensity diffuse_colour, float specular_amount, float specular_coeff,float reflect_fraction);

    Intensity diffuse_colour;
    float specular_amount;//[0,infinity]. 0 = matt
    float specular_coeff;//(0, infinity). for phong lighting
    float reflect_fraction;//[0,1]. 1 == total reflection, i.e. a.k.a shineness.dloat reflect_fractiona perfect mirror
};

#endif //WEKTORY_MATERIAL_H
