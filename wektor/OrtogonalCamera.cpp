#include "Camera.h"
#include "Image.h"
#include "Ray.h"
#include "Sphere.h"
#include "Intensity.h"
#include "OrtogonalCamera.h"
using namespace std;

OrtogonalCamera::OrtogonalCamera(Vector position, Vector target, Vector nearPlane, Vector farPlane, Vector up) : position(position), target(target), nearPlane(nearPlane), farPlane(farPlane), up(up) {

}

string OrtogonalCamera::showCoordinates() {
    return string("[(") + to_string(position.getX()) + string(", ") + to_string(position.getY()) + string(", ") + to_string(position.getZ()) +
           string("), (") + to_string(target.getX()) + string(", ") + to_string(target.getY()) + string(", ") + to_string(target.getZ()) +
           string("), (") + to_string(nearPlane.getX()) + string(", ") + to_string(nearPlane.getY()) + string(", ") + to_string(nearPlane.getZ()) +
           string("), (") + to_string(farPlane.getX()) + string(", ") + to_string(farPlane.getY()) + string(", ") + to_string(farPlane.getZ()) +
           string("), (") + to_string(up.getX()) + string(", ") + to_string(up.getY()) + string(", ") + to_string(up.getZ()) + string("]");
}


void render(){
    int szer;
    int wys;
    Image img = *new Image(szer, wys);
    for (int i = 0; i < img.width ; i++)
    {
        for (int j = 0; j < img.height; j++)
        {
            float srodekX = -1.0f + (i + 0.5f) * szer;
            float srodekY = 1.0f - (j + 0.5f) * wys;
            Vector null = *new Vector(0, 0, 0);
            Ray rayaner = *new Ray(*new Vector(0, 0, 1), *new Vector(srodekX, srodekY, 0));
            Sphere spherener = *new Sphere(*new Vector(0, 0, 0), 10);
            IntersectionResult przeciecie = spherener.Hit(rayaner,0,100);
//            if (przeciecie.type==HIT)
//            {
//                img.setPixel(i, j, kolor);
//            }
//            else img.setPixel(i, j, kolortla);
        }
    }
//    img.Bitmap.Save("obrazkoncowy.jpg");
//
}

