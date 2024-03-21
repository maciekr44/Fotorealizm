//
// Created by Kiu on 21.03.2024.
//

#ifndef WEKTORY_CAMERA_H
#define WEKTORY_CAMERA_H

#include "Ray.h"

class Camera {
public:
    virtual void render() = 0;
};

#endif //WEKTORY_CAMERA_H
