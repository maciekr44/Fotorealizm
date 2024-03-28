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

using namespace std;

float angle(Vector v1, Vector v2) {
    return acos(v1.dotProduct(v2) / (v1.length() * v2.length())) * 180 / M_PI;
}

float direction_angle(Vector v1) {
    Vector v2 = *new Vector(200,0,0);
    return acos(v1.dotProduct(v2) / (v1.length() * v2.length())) * 180 / M_PI;
}

int main() {

    Vector spherePoint1(10, 0, 0);
    Vector spherePoint2(28, 10, 5);
    Vector planePoint(100, 0, 0);
    Vector trianglePointA(2, 0, 0);
    Vector trianglePointB(2, 5, 0);
    Vector trianglePointC(2, 0, 5);

    Intensity color1(0.45,0.1,0.3);
    Intensity color2(0,1,0);
    Intensity color3(0.566,0.422,0.28);
    Intensity color4(0.566,0,0.48);

//    Sphere* sphere1 = new Sphere(spherePoint1, 5, color1);
//    Sphere* sphere2 = new Sphere(spherePoint2, 3, color3);


//    std::vector<Geometry*> sceneObjects;
//
//    sceneObjects.push_back(sphere1);
//    sceneObjects.push_back(sphere2);

    std::list<Geometry*> objects;
    objects.push_back(new Sphere(spherePoint1, 5, color1));
    objects.push_back(new Sphere(spherePoint2, 3, color3));
    objects.push_back(new Plane(Vector(1, 0, 0), planePoint, color2));
    objects.push_back(new Triangle(trianglePointA, trianglePointB, trianglePointC, color4));



    Image image(500, 500);

    Vector cameraPositionOrto(-40, 0, 0);  // Set the camera position
    Vector lookAtOrto(-30, 0, 0);  // Set the point to look at
    Ray directionOrtoRay(cameraPositionOrto, lookAtOrto);
    Vector directionOrtoVector = directionOrtoRay.getDirection();
    Vector directionOrtoVectorTMP = directionOrtoRay.getDirection();
    Vector upOrto = directionOrtoVector.findPerpendicularVector(directionOrtoVectorTMP);

    Vector finish(0,0,0);
    Vector start(0,0,0);


// Create an orthographic camera
    OrtogonalCamera cameraOrto(cameraPositionOrto, lookAtOrto, upOrto);
    Ray rayOrthographic (cameraPositionOrto,lookAtOrto);

    //ray uzywany do antyaliasingu
    Ray raySampling(Vector(0, 0, 0), Vector(100, 0, 0));


    // Iterate over each pixel in the image
    for (int y = 0; y < image.height; ++y) {
        for (int x = 0; x < image.width; ++x) {

            directionOrtoRay.setOrigin(cameraPositionOrto);
            directionOrtoRay.setDestination(lookAtOrto);


            float pixelX = (-1.0f + 2.0f * x / (image.width - 1.0f)) * directionOrtoRay.getDistance();
            float pixelY = (-1.0f + 2.0f * y / (image.height - 1.0f)) * directionOrtoRay.getDistance();

            int sampling = 5;

            float antialiasingPixelSize = ((directionOrtoRay.getDistance() * 2) / image.width) / sampling;

            float antialiasingPixelX = pixelX - (2 * antialiasingPixelSize);
            float antialiasingPixelY = pixelY - (2 * antialiasingPixelSize);


            Vector rayDirection = directionOrtoRay.getDirection();
            float cameraEnd = rayDirection.getX();

            finish.setX(cameraEnd);
            finish.setY(pixelY);
            finish.setZ(pixelX);

            float cameraPoint = cameraPositionOrto.getX();
            start.setX(cameraPoint);
            start.setY(pixelY);
            start.setZ(pixelX);

            rayOrthographic.setOrigin(start);
            rayOrthographic.setDestination(finish);


            // ANTYALIASING

            Vector raySamplingOrigin(0, antialiasingPixelY, antialiasingPixelX);
            raySampling.setOrigin(raySamplingOrigin);
            Vector raySamplingDestination(100, antialiasingPixelY, antialiasingPixelX);
            raySampling.setDestination(raySamplingDestination);

            Intensity meanColor = OrtogonalCamera::antyaliasingOrto(sampling, antialiasingPixelY, antialiasingPixelX, antialiasingPixelSize, raySampling, objects, rayOrthographic);
            image.setPixel(x, y, meanColor);
        }
    }

    // Create SFML window
    sf::RenderWindow window(sf::VideoMode(image.width, image.height), "SFML Image");

    // Main loop
    while (window.isOpen()) {
        // Process events
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Clear window
        window.clear();

        // Draw the image
        window.draw(image);

        // Display window
        window.display();
    }


    // Define the parameters for the camera
    Vector cameraPositionPersp(-40, 0, 0);  // Set the camera position
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


    for (int y = 0; y < image.height; ++y) {
        for (int x = 0; x < image.width; ++x) {

            float aspectRatio = (float)image.width / image.height;
            float halfHeight = tan(fov * 3.14159 / 360.0f);
            float halfWidth = aspectRatio * halfHeight;

            float pixelX = ((2.0f * (x + 0.5f) / (float)image.width - 1) * halfWidth) * directionPerspRay.getDistance();
            float pixelY = (( 2.0f * (y + 0.5f) / (float)image.height - 1) * halfHeight) * directionPerspRay.getDistance();

            int sampling = 5;
            float antialiasingPixelSize = ((directionPerspRay.getDistance() * 2) / image.width) / sampling;
            float antialiasingPixelX = pixelX - (2 * antialiasingPixelSize);
            float antialiasingPixelY = pixelY - (2 * antialiasingPixelSize);

            float cameraEnd = directionVector.getX();

            Vector finish(cameraEnd, pixelY, pixelX);
            float cameraPoint = cameraPositionOrto.getX();
            Vector start(cameraPoint, pixelY, pixelX);

            Ray raySampling(cameraPositionOrto, finish);


            Ray rayOrthographic(cameraPositionOrto, finish);
            // Check for intersections with the sphere
            Intensity meanColor = PerspectiveCamera::antyaliasingPersp(sampling, antialiasingPixelY, antialiasingPixelX, antialiasingPixelSize, raySampling, objects, rayOrthographic);
            image.setPixel(x, y, meanColor);
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

    for (auto obj : objects) {
        delete obj;
    }
}



