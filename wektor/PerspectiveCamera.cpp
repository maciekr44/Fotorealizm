//
// Created by Kiu on 21.03.2024.
//

using namespace std;
#include "PerspectiveCamera.h"
#include "Image.h"

PerspectiveCamera::PerspectiveCamera(Vector position, Vector target, Vector nearPlane, Vector farPlane, Vector up, float fov) : position(position), target(target), nearPlane(nearPlane), farPlane(farPlane), up(up), fov(fov) {

}

string PerspectiveCamera::showCoordinates() {
    return string("[(") + to_string(position.getX()) + string(", ") + to_string(position.getY()) + string(", ") + to_string(position.getZ()) +
           string("), (") + to_string(target.getX()) + string(", ") + to_string(target.getY()) + string(", ") + to_string(target.getZ()) +
           string("), (") + to_string(nearPlane.getX()) + string(", ") + to_string(nearPlane.getY()) + string(", ") + to_string(nearPlane.getZ()) +
           string("), (") + to_string(farPlane.getX()) + string(", ") + to_string(farPlane.getY()) + string(", ") + to_string(farPlane.getZ()) +
           string("), (") + to_string(up.getX()) + string(", ") + to_string(up.getY()) + string(", ") + to_string(up.getZ()) +
           string("), ") + to_string(fov) +  string("]");
}


