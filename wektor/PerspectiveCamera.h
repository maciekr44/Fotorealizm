#include "Vector.h"
#include "Ray.h"


class PerspectiveCamera {
private:
    Vector position;
    Vector lookAt;
    Vector up;
    float _fov;
    int _widthPersp;// pole widzenia
    int _heightPersp;
public:
    PerspectiveCamera(Vector _position, Vector _lookAt, Vector _up, float _fov, int _widthPersp, int _heightPersp);
    
    // Calculate the right vector based on the up vector and the direction from camera position to lookAt
    Vector right() const {
        Vector direction = lookAt;
        direction.sub(position);
        Vector right = direction.cross(up);
        //right.normalize();
        return right;
    }
};
