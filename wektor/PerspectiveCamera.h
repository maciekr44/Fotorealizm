//
// Created by Kiu on 21.03.2024.
//

#ifndef WEKTORY_PERSPECTIVECAMERA_H
#define WEKTORY_PERSPECTIVECAMERA_H

#include "Camera.h"


class PerspectiveCamera : public Camera {
public:
    Vector position;
    Vector target;
    Vector nearPlane;
    Vector farPlane;
    Vector up;
    float fov;

    PerspectiveCamera(Vector position, Vector target, Vector nearPlane, Vector farPlane, Vector up, float fov);

    std::string showCoordinates();

    void render() override {
        std::cout << "Rendering using Perspective Camera...\n";
        // Implementacja renderowania dla kamery perspektywicznej
    }

};


#endif //WEKTORY_PERSPECTIVECAMERA_H
