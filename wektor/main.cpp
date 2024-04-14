#include <iostream>
#include <string>
#include <limits>
#include <SFML/Graphics.hpp>
#include <list>
#include "Vector.h"
//#include "Ray.h"
//#include "Intensity.h"
#include "PerspectiveCamera.h"
#include "Image.h"
#include "OrtogonalCamera.h"
//#include "Geometry.h"
#include "Plane.h"
#include "Sphere.h"
#include "Triangle.h"
#include "PointLight.h"
#include "Material.h"
#include "AmbientLight.h"

using namespace std;

float angle(Vector v1, Vector v2) {
    return acos(v1.dotProduct(v2) / (v1.length() * v2.length())) * 180 / M_PI;
}

float direction_angle(Vector v1) {
    Vector v2 = *new Vector(200,0,0);
    return acos(v1.dotProduct(v2) / (v1.length() * v2.length())) * 180 / M_PI;
}

int main() {

    Vector spherePoint1(10, 3, -1);
    Vector spherePoint2(4, 0, 0);
    Vector planePoint(15, 0, 0);
    Vector planePoint1(14, 7, 0);
    Vector planePoint2(14, -7, 0);
    Vector planePoint3(14, 0, 7);
    Vector planePoint4(14, 0, -7);




    Vector trianglePointB(-8, 6, 0);
    Vector trianglePointC(-8, 0, 6);
    Vector trianglePointA(-8, 0, 0);//X działa odwrotnie niż w kamerach tamto -8 to u nas 8

    Intensity color1(1, 0, 0);
    Intensity color2(0, 0.5, 0.5);
    Intensity color3(1, 1, 1);
    Intensity color4(1, 0, 0);
    Intensity color5(0, 0.5, 0);
    Intensity color6(0.5, 0, 0.5);


    // mniejsze specular to wieksza matowosc
    // mniejsze shininess to ostrzejsza krawedz swiatla
    // reflect nic nie robi narazie
    Material material1(color1, 0.1, 1, 1);
    Material material2(color2, 10, 10, 1);
    Material material3(color3, 1, 1, 1);
    Material material4(color4, 1, 1, 1);
    Material material5(color5, 1, 1, 1);


    std::list<Geometry *> objects;
    objects.push_back(new Sphere(spherePoint1, 4, material1));
    objects.push_back(new Sphere(spherePoint2, 1.5, material2));
    objects.push_back(new Plane(Vector(-1, 0, 0), planePoint, material3));
    objects.push_back(new Plane(Vector(-0.8, -1, 0), planePoint1, material3)); //podloga
    objects.push_back(new Plane(Vector(-0.8, 1, 0), planePoint2, material3)); //sufit
    objects.push_back(new Plane(Vector(-1, 0, -0.8), planePoint3, material3)); //lewa sciana
    objects.push_back(new Plane(Vector(-1, 0, 0.8), planePoint4, material3)); // prawa sciana




//    objects.push_back(new Triangle(trianglePointA, trianglePointB, trianglePointC, material4));

    Image image(500, 500);

    Vector cameraPositionOrto(-40, 0, 0);  // Set the camera position
    Vector lookAtOrto(-30, 0, 0);  // Set the point to look at
    Ray directionOrtoRay(cameraPositionOrto, lookAtOrto);
    Vector directionOrtoVector = directionOrtoRay.getDirection();
    Vector directionOrtoVectorTMP = directionOrtoRay.getDirection();
    Vector upOrto = directionOrtoVector.findPerpendicularVector(directionOrtoVectorTMP);

    Vector finish(0, 0, 0);
    Vector start(0, 0, 0);

    AmbientLight ambientLight = AmbientLight(color3, 0.0);
    Vector lightPosition(-1,-1,2);


//
//// Create an orthographic camera
//    OrtogonalCamera cameraOrto(cameraPositionOrto, lookAtOrto, upOrto);
//    Ray rayOrthographic (cameraPositionOrto,lookAtOrto);
//
//    //ray uzywany do antyaliasingu
//    Ray raySampling(Vector(0, 0, 0), Vector(100, 0, 0));
//
//
//    // Iterate over each pixel in the image
//    for (int y = 0; y < image.height; ++y) {
//        for (int x = 0; x < image.width; ++x) {
//
//            directionOrtoRay.setOrigin(cameraPositionOrto);
//            directionOrtoRay.setDestination(lookAtOrto);
//
//
//            float pixelX = (-1.0f + 2.0f * x / (image.width - 1.0f)) * directionOrtoRay.getDistance();
//            float pixelY = (-1.0f + 2.0f * y / (image.height - 1.0f)) * directionOrtoRay.getDistance();
//
//            int sampling = 5;
//
//            float antialiasingPixelSize = ((directionOrtoRay.getDistance() * 2) / image.width) / sampling;
//
//            float antialiasingPixelX = pixelX - (2 * antialiasingPixelSize);
//            float antialiasingPixelY = pixelY - (2 * antialiasingPixelSize);
//
//
//            Vector rayDirection = directionOrtoRay.getDirection();
//            float cameraEnd = rayDirection.getX();
//
//            finish.setX(cameraEnd);
//            finish.setY(pixelY);
//            finish.setZ(pixelX);
//
//            float cameraPoint = cameraPositionOrto.getX();
//            start.setX(cameraPoint);
//            start.setY(pixelY);
//            start.setZ(pixelX);
//
//            rayOrthographic.setOrigin(start);
//            rayOrthographic.setDestination(finish);
//
//
//            // ANTYALIASING
//
//            Vector raySamplingOrigin(0, antialiasingPixelY, antialiasingPixelX);
//            raySampling.setOrigin(raySamplingOrigin);
//            Vector raySamplingDestination(100, antialiasingPixelY, antialiasingPixelX);
//            raySampling.setDestination(raySamplingDestination);
//
//            Material meanColor = OrtogonalCamera::antyaliasingOrto(sampling, antialiasingPixelY, antialiasingPixelX, antialiasingPixelSize, raySampling, objects, rayOrthographic);
//            image.setPixel(x, y, meanColor.color); //todo: zmienic kolor na material
//        }
//    }
//
//    // Create SFML window
//    sf::RenderWindow window(sf::VideoMode(image.width, image.height), "SFML Image");
//
//    // Main loop
//    while (window.isOpen()) {
//        // Process events
//        sf::Event event;
//        while (window.pollEvent(event)) {
//            if (event.type == sf::Event::Closed)
//                window.close();
//        }
//
//        // Clear window
//        window.clear();
//
//        // Draw the image
//        window.draw(image);
//
//        // Display window
//        window.display();
//    }


    // Define the parameters for the camera
    Vector cameraPositionPersp(-39, 0, 0);  // Set the camera position
    Vector lookAtPersp(-30, 0, 0);  // Set the point to look at

    Ray directionPerspRay(cameraPositionPersp, lookAtPersp);
    Vector directionPerspVector = directionPerspRay.getDirection();
    Vector directionPerspVectorTMP = directionPerspRay.getDirection();
    Vector upPersp = directionPerspVector.findPerpendicularVector(directionPerspVectorTMP);
    float fov = 90.0f;

// Create a perspective camera
    PerspectiveCamera cameraPersp(cameraPositionPersp, lookAtPersp, upPersp, fov);
    Ray directionRay(cameraPositionOrto, lookAtOrto);
    Vector directionVector = directionRay.getDirection();
    PointLight nowy = PointLight();
    nowy.location = lightPosition;
    nowy.constAtten = 0.7; // jak mniejsze to ciemniej
    nowy.linearAtten = 0.05; // jak mniejsze to jasniej
    nowy.color = color3;


    for (int y = 0; y < image.height; ++y) {
        for (int x = 0; x < image.width; ++x) {

            float aspectRatio = (float) image.width / image.height;
            float halfHeight = tan(fov * M_PI / 360.0f);
            float halfWidth = aspectRatio * halfHeight;

            float pixelX =
                    ((2.0f * (x + 0.5f) / (float) image.width - 1) * halfWidth) * directionPerspRay.getDistance();
            float pixelY =
                    ((2.0f * (y + 0.5f) / (float) image.height - 1) * halfHeight) * directionPerspRay.getDistance();

            int sampling = 5;
            float antialiasingPixelSize = ((directionPerspRay.getDistance() * 2) / image.width) / sampling;
            float antialiasingPixelX = pixelX - (2 * antialiasingPixelSize);
            float antialiasingPixelY = pixelY - (2 * antialiasingPixelSize);

            float cameraEnd = directionVector.getX();

            Vector finish(cameraEnd, pixelY, pixelX);
            float cameraPoint = cameraPositionOrto.getX();
            Vector start(cameraPoint, pixelY, pixelX);

            Ray raySampling(cameraPositionPersp, finish);

            Ray rayPerspective(cameraPositionPersp, finish);
            Ray objectToLight(finish, nowy.location);
//            cout<<nowy.location.showCoordinates()<<endl;
//            cout<<objectToLight.showCoordinates()<<endl;

            IntersectionResult closestIntersection;
            closestIntersection.type = MISS;
            for (auto obj: objects) {  //jednym z obiektow winien byc farplane
                IntersectionResult intersection = obj->collision(objectToLight, 0, 1000);
                if (intersection.type == HIT && intersection.distance < closestIntersection.distance) {
                    closestIntersection = intersection;
                }
            }
//            if (closestIntersection.type == MISS) {
            Material meanColor = PerspectiveCamera::antyaliasingPersp(sampling, antialiasingPixelY,
                                                                      antialiasingPixelX,
                                                                      antialiasingPixelSize, raySampling, objects,
                                                                      rayPerspective, nowy, start, finish,
                                                                      ambientLight);

            image.setPixel(x, y, meanColor.color); //todo: zmienic kolor na material
//            } else {
//                Intensity Red(1,0,1);
//                Material meanColor(Red,0,0,0);
//                image.setPixel(x, y, meanColor.color); //todo: zmienic kolor na material
////                cout<<"NIE KUPA"<<endl;
//            }


        }
    }

    // Create SFML window
    sf::RenderWindow window1(sf::VideoMode(image.width, image.height), "SFML Image");

    // Main loop
    while (window1.isOpen()) {
        // Process events
        sf::Event event;
        while (window1.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window1.close();
        }

        // Clear window
        window1.clear();

        // Draw the image
        window1.draw(image);

        // Display window
        window1.display();
    }

    for (auto obj: objects) {
        delete obj;
    }

}