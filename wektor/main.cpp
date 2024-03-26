#include <iostream>
#include <string>
#include <limits>
#include <SFML/Graphics.hpp>
#include "Vector.h"
#include "Sphere.h"
#include "Ray.h"
#include "Plane.h"
#include "Triangle.h"
#include "Intensity.h"
#include "PerspectiveCamera.h"
#include "Image.h"
#include "OrtogonalCamera.h"

using namespace std;

float angle(Vector v1, Vector v2) {
    return acos(v1.dotProduct(v2) / (v1.length() * v2.length())) * 180 / M_PI;
}

float direction_angle(Vector v1) {
    Vector v2 = *new Vector(200,0,0);
    return acos(v1.dotProduct(v2) / (v1.length() * v2.length())) * 180 / M_PI;
}

int main() {

    Vector spher_point = *new Vector(0, 0, 0);
    Vector spher_point2 = *new Vector(28, 10, 0);

    Intensity color1 = *new Intensity(1,0,0);
    Intensity color2 = *new Intensity(0,1,0);
    Intensity color3 = *new Intensity(0,0,1);
    Sphere s1 = *new Sphere(spher_point, 5, color1);
    Sphere s2 = *new Sphere(spher_point2, 3, color3);

    cout<<s1.showCoordinates()<<endl;
    cout<<s1.getColor().getRed()<<endl;
    cout<<s1.getColor().getGreen()<<endl;
    cout<<s1.getColor().getBlue()<<endl;

    // Create an image with given width and height
    Image image(500, 500);

    Vector cameraPositionOrto(-40, 0, 0);  // Set the camera position
    Vector lookAtOrto(-30, 0, 0);  // Set the point to look at
    Ray kierunek = *new Ray(cameraPositionOrto, lookAtOrto);
    Vector zwrot = kierunek.getDirection();
    Vector prostopadly = kierunek.getDirection();
    Vector upOrto = zwrot.findPerpendicularVector(prostopadly);
    cout<<"prostopadly" <<zwrot.showCoordinates()<<endl;
    cout<<"prostopadly" <<prostopadly.showCoordinates()<<endl;
    cout<<"Up orto "<<upOrto.showCoordinates()<<endl;
 //   Vector upOrto(0, 0, 1);  // Set the up vector
    float leftOrto = -100.0f;   // Set the left boundary of the view frustum
    float rightOrto = 100.0f;   // Set the right boundary of the view frustum
    float bottomOrto = -100.0f; // Set the bottom boundary of the view frustum
    float topOrto = 100.0f;     // Set the top boundary of the view frustum

//    Ray kierunek = *new Ray(cameraPositionOrto, lookAtOrto);
    Vector finish = *new Vector(0,0,0);
    Vector start = *new Vector(0,0,0);


// Create an orthographic camera
    OrtogonalCamera cameraOrto(cameraPositionOrto, lookAtOrto, upOrto, leftOrto, rightOrto, bottomOrto, topOrto, image.width, image.height);
    Ray rayOrthographic = *new Ray(cameraPositionOrto,lookAtOrto);

    Ray raySampling = *new Ray(*new Vector(0, 0, 0), *new Vector(100, 0, 0));


    // Iterate over each pixel in the image
    for (int y = 0; y < image.height; ++y) {
        for (int x = 0; x < image.width; ++x) {

            kierunek.setOrigin(cameraPositionOrto);
            kierunek.setDestination(lookAtOrto);
//            kierunek = Ray(cameraPositionOrto, lookAtOrto);

            float u = (-1.0f + 2.0f * x / (image.width - 1.0f)) * kierunek.getDistance();
            float v = (-1.0f + 2.0f * y / (image.height - 1.0f)) * kierunek.getDistance();
            int sampling = 5;

            float szerokosc = ((kierunek.getDistance()*2)/image.width)/sampling;
//            cout<<"Szerokosc"<<szerokosc<<endl;
            float pointU = u - (2 * szerokosc);
            float pointV = v - (2 * szerokosc);
//            cout<<"U "<<pointU<<endl;
//            cout<<"V "<<pointV<<endl;


            Vector zwrot = kierunek.getDirection();
            float cameraEnd = zwrot.getX();

//            Vector finish = *new Vector(cameraEnd, v, u);
            finish.setX(cameraEnd);
            finish.setY(v);
            finish.setZ(u);

            float cameraPoint = cameraPositionOrto.getX();
//            Vector start = *new Vector(cameraPoint, v, u);
            start.setX(cameraPoint);
            start.setY(v);
            start.setZ(u);
//            Vector start = rayOrthographic.getDirection();
//            cout<<start.showCoordinates()<<endl;
//            cout<<finish.showCoordinates()<<endl;


//            Ray rayOrthographic = *new Ray(start, finish);
            rayOrthographic.setOrigin(start);
            rayOrthographic.setDestination(finish);


            // ANTYALIASING
            int iterator = 0;

//            Ray raySampling = *new Ray(*new Vector(0, pointV, pointU), *new Vector(100, pointV, pointU));
            Vector raySamplingOrigin(0, pointV, pointU);
            raySampling.setOrigin(raySamplingOrigin);
            Vector raySamplingDestination(100, pointV, pointU);
            raySampling.setOrigin(raySamplingDestination);

            Intensity sredni = OrtogonalCamera::antyaliasingOrto(sampling, pointV, pointU, szerokosc, raySampling, s1, s2, rayOrthographic,  iterator);
//            cout << sredni.getRed() << "; " << sredni.getGreen() << "; "  << sredni.getBlue() << endl;
            image.setPixel(x, y, sredni);
//            cout << sredni.R() << "; " << sredni.G() << "; " << sredni.B() << endl;


            // ----------------------------------

        }
    }

    // Create SFML window
    sf::RenderWindow window(sf::VideoMode(image.width, image.height), "SFML Image Test");

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
    Vector cameraPosition(-40, 0, 0);  // Set the camera position
    Vector lookAt(-30, 0, 0);  // Set the point to look at

    Ray kierunek1 = *new Ray(cameraPosition, lookAt);
    Vector zwrot1 = kierunek1.getDirection();
    Vector prostopadly1 = kierunek1.getDirection();
    Vector up1 = zwrot1.findPerpendicularVector(prostopadly1);
    float fov = 180.0f;

// Create a perspective camera
    PerspectiveCamera cameraPersp(cameraPosition, lookAt, up1, fov, image.width, image.height);

// Iterate over each pixel in the image
    for (int y = 0; y < image.height; ++y) {
        for (int x = 0; x < image.width; ++x) {

            float fov = -90.0f; // kąt widzenia kamery
            float aspectRatio = (float)image.width / image.height;
            float halfHeight = tan(fov * 3.14159 / 360.0f);
            float halfWidth = aspectRatio * halfHeight;

            Ray kierunek = *new Ray(cameraPositionOrto, lookAtOrto);
            float u = ((2.0f * (x + 0.5f) / (float)image.width - 1) * halfWidth)*10;
            float v = ((1 - 2.0f * (y + 0.5f) / (float)image.height) * halfHeight)*10;

            Vector zwrot = kierunek.getDirection();
            float cameraEnd = zwrot.getX();

            Vector finish = *new Vector(cameraEnd, v, u);
            float cameraPoint = cameraPositionOrto.getX();
            Vector start = *new Vector(cameraPoint, v, u);


            Ray rayOrthographic = *new Ray(cameraPositionOrto, finish);
            // Check for intersections with the sphere
            IntersectionResult intersectionOrthographic = s1.Hit(rayOrthographic, 0, 900);  //tmax to ten nasz far plane
            IntersectionResult intersectionOrthographicS2 = s2.Hit(rayOrthographic, 0,
                                                                   900);  //tmax to ten nasz far plane


            if (intersectionOrthographic.type == HIT && intersectionOrthographicS2.type != HIT) {
                image.setPixel(x, y, intersectionOrthographic.color);
            } else if (intersectionOrthographicS2.type == HIT && intersectionOrthographic.type != HIT) {
                image.setPixel(x, y, intersectionOrthographicS2.color);
            } else if (intersectionOrthographic.type == HIT && intersectionOrthographicS2.type == HIT) {
                // Choose the closest intersection
                if (intersectionOrthographic.distance < intersectionOrthographicS2.distance) {
                    image.setPixel(x, y, intersectionOrthographic.color);
                } else {
                    image.setPixel(x, y, intersectionOrthographicS2.color);
                }
            } else {
                // Set background color
                Intensity bgColor(0, 1, 1);
                image.setPixel(x, y, bgColor);
            }
        }
    }
    // Create SFML window
    sf::RenderWindow window1(sf::VideoMode(image.width, image.height), "SFML Image Test");

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
}



