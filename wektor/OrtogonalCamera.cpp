//#include "Camera.h"
//#include "Image.h"
//#include "Ray.h"
//#include "Sphere.h"
//#include "Intensity.h"
//#include "OrtogonalCamera.h"
//using namespace std;
//
//OrtogonalCamera::OrtogonalCamera(Vector position, Vector target, Vector nearPlane, Vector farPlane, Vector up) : position(position), target(target), nearPlane(nearPlane), farPlane(farPlane), up(up) {
//
//}
//
//string OrtogonalCamera::showCoordinates() {
//    return string("[(") + to_string(position.getX()) + string(", ") + to_string(position.getY()) + string(", ") + to_string(position.getZ()) +
//           string("), (") + to_string(target.getX()) + string(", ") + to_string(target.getY()) + string(", ") + to_string(target.getZ()) +
//           string("), (") + to_string(nearPlane.getX()) + string(", ") + to_string(nearPlane.getY()) + string(", ") + to_string(nearPlane.getZ()) +
//           string("), (") + to_string(farPlane.getX()) + string(", ") + to_string(farPlane.getY()) + string(", ") + to_string(farPlane.getZ()) +
//           string("), (") + to_string(up.getX()) + string(", ") + to_string(up.getY()) + string(", ") + to_string(up.getZ()) + string("]");
//}
//
//
