//
// Created by Kiu on 21.03.2024.
//

#ifndef WEKTORY_ORTOGONALCAMERA_H
#define WEKTORY_ORTOGONALCAMERA_H

#include "Camera.h"

class OrtogonalCamera : public Camera {
public:
    Vector position;
    Vector target;
    Vector nearPlane;
    Vector farPlane;
    Vector up;

    OrtogonalCamera(Vector position, Vector target, Vector nearPlane, Vector farPlane, Vector up);

    std::string showCoordinates();

    void render() override {
        std::cout << "Rendering using Perspective Camera...\n";
        // Implementacja renderowania dla kamery perspektywicznej
    }

};


#endif //WEKTORY_ORTOGONALCAMERA_H
