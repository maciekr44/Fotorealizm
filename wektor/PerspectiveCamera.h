//
// Created by Kiu on 21.03.2024.
//

#ifndef WEKTORY_PERSPECTIVECAMERA_H
#define WEKTORY_PERSPECTIVECAMERA_H

#include "Camera.h"


#include "Vector.h" // Include your Vector class here
#include "Ray.h"    // Include your Ray class here

class PerspectiveCamera {
private:
    Vector position;    // Position of the camera
    Vector target;      // Point the camera is looking at
    Vector up;          // Up direction of the camera
    float fov;          // Field of view angle in degrees
    int imageWidth;     // Width of the image
    int imageHeight;    // Height of the image

public:
    // Constructor to initialize the perspective camera
    PerspectiveCamera(Vector _position, Vector _target, Vector _up, float _fov, int _imageWidth, int _imageHeight)
            : position(_position), target(_target), up(_up), fov(_fov), imageWidth(_imageWidth), imageHeight(_imageHeight) {}

    // Function to cast a ray through a pixel in the image
    Ray castRay(int pixelX, int pixelY) {
        // Calculate the direction of the ray based on the pixel position
        // Assume the image plane is at z = 1
        float aspectRatio = static_cast<float>(imageWidth) / static_cast<float>(imageHeight);
        float halfWidth = tan(fov * 0.5f * (M_PI / 180.0f));
        float halfHeight = halfWidth / aspectRatio;
        float x = (2.0f * (pixelX + 0.5f) / static_cast<float>(imageWidth) - 1.0f) * halfWidth;
        float y = (1.0f - 2.0f * (pixelY + 0.5f) / static_cast<float>(imageHeight)) * halfHeight;

        // Calculate the direction vector
        Vector originTarget = target;
        Vector originUp = up;
        target.sub(position);
        target.normalize();
        up.mag(y);
        target.add(up);
        originTarget.sub(position);
        originTarget.normalize();
        originUp.cross(originTarget);
        originUp.mag(x);
        target.add(up);
        target.add(originUp);

        Vector direction = originTarget;

        // Return a ray starting from the camera position and going in the calculated direction
        return Ray(position, direction);
    }
};


#endif //WEKTORY_PERSPECTIVECAMERA_H
