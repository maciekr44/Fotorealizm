#include "Vector.h"

class OrtogonalCamera {
public:
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
    OrtogonalCamera(Vector _positionOrto, Vector _lookAtOrto, Vector _upOrto, float _leftOrto, float _rightOrto,
                    float _bottomOrto, float _topOrto, int _widthOrto, int _heightOrto);

};