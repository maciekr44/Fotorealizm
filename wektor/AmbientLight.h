//
// Created by Kiu on 11.04.2024.
//

#ifndef WEKTORY_AMBIENTLIGHT_H
#define WEKTORY_AMBIENTLIGHT_H

#include "Intensity.h"

class AmbientLight {
private:
    Intensity color;
    float intensity;

public:
    AmbientLight(const Intensity& color, float intensity) : color(color), intensity(intensity) {}

    Intensity getColor() const { return color; }
    float getIntensity() const { return intensity; }

    void setColor(const Intensity& color) { this->color = color; }
    void setIntensity(float intensity) { this->intensity = intensity; }
};


#endif //WEKTORY_AMBIENTLIGHT_H
