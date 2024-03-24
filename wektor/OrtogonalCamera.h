#include "Vector.h"

class OrtogonalCamera {
private:
    Vector positionOrto;
    Vector lookAtOrto;
    Vector upOrto;
    float leftOrto;
    float rightOrto;
    float bottomOrto;
    float topOrto;
    int widthOrto;
    int heightOrto;

public:
    OrtogonalCamera(Vector _positionOrto, Vector _lookAtOrto, Vector _upOrto, float _leftOrto, float _rightOrto, float _bottomOrto, float _topOrto, int _widthOrto, int _heightOrto)
            : positionOrto(_positionOrto), lookAtOrto(_lookAtOrto), upOrto(_upOrto), leftOrto(_leftOrto), rightOrto(_rightOrto), bottomOrto(_bottomOrto), topOrto(_topOrto), widthOrto(_widthOrto), heightOrto(_heightOrto) {}

    // Function to cast a ray from the camera to a pixel on the image plane
    Vector castRay(int x, int y) {
        // Calculate the direction vector from the camera position to the pixel on the image plane
        float pixelX = leftOrto + (rightOrto - leftOrto) * (x + 0.5f) / widthOrto;
        float pixelY = topOrto + (bottomOrto - topOrto) * (y + 0.5f) / heightOrto;

        // Calculate the direction vector using the rightO function

        Ray ray = *new Ray(positionOrto, lookAtOrto);
        Vector directionOrto = *new Vector;
        directionOrto = ray.getDirection();

        // Return the ray
        return Vector(directionOrto);
    }

//private:
    // Calculate the right vector based on the up vector and the direction from camera position to lookAt
//    Vector rightO() {
//        Vector directionOrto = lookAtOrto - positionOrto;
//        Vector rightOrto = directionOrto.cross(upOrto);
//        rightOrto.normalize();
//        return rightOrto;
//    }
};
