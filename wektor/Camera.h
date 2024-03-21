//
// Created by Kiu on 21.03.2024.
//

#ifndef WEKTORY_CAMERA_H
#define WEKTORY_CAMERA_H

#include "Ray.h"

class Camera {
public:
    virtual Ray getRay(float u, float v) const = 0;

private:
    Vector position;
    Vector target;  //wektor kierunkowy kamery
    Vector nearPlane;
    Vector farPlane;
    Vector up; //gora wzgledem kamery
};


#endif //WEKTORY_CAMERA_H
