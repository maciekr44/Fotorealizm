#include "Camera.h"

class OrthographicCamera : public Camera {
public:
    Vector position;
    Vector target;
    Vector nearPlane;
    Vector farPlane;
    Vector up;
    float fov;

    OrthographicCamera(const Vector& _position, const Vector& _target, const Vector& _nearPlane, const Vector& _farPlane, const Vector& _up)
            : position(_position), target(_target), nearPlane(_nearPlane), farPlane(_farPlane), up(_up), fov(0) {}

    void render() override {
        std::cout << "Rendering using Orthographic Camera...\n";
        // Implementacja renderowania dla kamery ortograficznej
    }
};