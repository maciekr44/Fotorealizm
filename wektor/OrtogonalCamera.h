#include "Vector.h"

class OrtogonalCamera {
private:
    Vector position;
    Vector lookAt;
    Vector up;
    float left;
    float right;
    float bottom;
    float top;
    int imageWidth;
    int imageHeight;

public:
    OrtogonalCamera(Vector pos, Vector look, Vector upVec, float leftBound, float rightBound,
                     float bottomBound, float topBound, int width, int height)
            : position(pos), lookAt(look), up(upVec), left(leftBound), right(rightBound),
              bottom(bottomBound), top(topBound), imageWidth(width), imageHeight(height) {}

    Ray castRay(int x, int y) { // x i y to wspolrzedne image
        float u = left + (right - left) * (x + 0.5f) / imageWidth;
        float v = bottom + (top - bottom) * (y + 0.5f) / imageHeight;

        lookAt.sub(position);
        lookAt.normalize();
        Vector rightVector = up.cross(lookAt);
        rightVector.normalize();
        Vector upVector = lookAt.cross(rightVector);
        upVector.normalize();
        Vector rayDirection = lookAt;
        rightVector.mag(u);
        rayDirection.add(rightVector);
        upVector.mag(v);
        rayDirection.add(upVector);

        rayDirection.add(position);

    Vector position1(u, v, position.getZ());


        return Ray(position1, rayDirection);
    }
};