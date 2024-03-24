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
    Vector w1 = *new Vector(1, 2, 3);
    Vector w2 = *new Vector(4, 5, 6);
    Vector w3 = *new Vector(0, 3, 0);
    Vector w4 = *new Vector(5, 5, 0);
    Vector w5 = *new Vector(4, 5, 1);
    Vector w6 = *new Vector(4, 1, 3);

    Vector w90 = *new Vector(1, 1, 0);

    Vector spher_point = *new Vector(0, 0, 20);
    Intensity color1 = *new Intensity(1, 0, 0);
    Intensity color2 = *new Intensity(0, 1, 0);
    Intensity color3 = *new Intensity(0, 0, 1);
    Sphere s1 = *new Sphere(spher_point, 10, color1);

    Vector ray_point = *new Vector(0, 0, -20);
    Ray r1 = *new Ray(spher_point, ray_point);

    Vector parallel = *new Vector(0, 40, -20);
    Ray r2 = *new Ray(ray_point, parallel);

    Vector third_origin = *new Vector(8, -12, 0);
    Vector third_destination = *new Vector(3, -2, 0);
    Ray r3 = *new Ray(third_origin, third_destination);

    Vector angle45 = *new Vector(0, 1, 1);
    Plane p1 = *new Plane(angle45, spher_point, color2);

    cout << "\nZad 1\n" << endl;
    cout << "Zaimplementowalismy klase wektor wraz ze wszystkimi dzialaniami." << endl;

    cout << "\nZad 2\n" << endl;
    cout << "V1: " << w1.showCoordinates() << endl;
    cout << "V2: " << w2.showCoordinates() << endl;
    w1.add(w2);

    cout << "Suma wektorow:" << endl;
    cout << "V1 + V2 = " << w1.showCoordinates() << endl;

    w1.sub(w2);
    w2.add(w1);
    cout << "V2 + V1 = " << w2.showCoordinates() << endl;


    cout << "\nZad 3\n" << "V1: " << w3.showCoordinates() << "\nV2: " << w4.showCoordinates() << endl;
    cout << "Kat wynosi: " << to_string(angle(w3, w4)) << " stopni" << endl;

    cout << "\nZad 4\n" << "V1: " << w5.showCoordinates() << "\nV2: " << w6.showCoordinates() << endl;
    Vector prostopadly = w5.cross(w6);
    cout << "Wektor prostopadly do obu poprzednich ma wspolrzedne: " << prostopadly.showCoordinates() << endl;

    cout << "\nZad 5\n";
    prostopadly.normalize();
    cout << "Znormalizowany poprzedni wektor prostopadly ma wspolrzedne: " << prostopadly.showCoordinates() << endl;

    cout << "\nZad 6\n";
    cout << "Zaimplementowalismy klasy promien, sfera i plaszczyzna." << endl;

    cout << "\nZad 7\n";
    cout << "S1: " << s1.showCoordinates() << endl;

    cout << "\nZad 8\n";
    cout << "R1: " << r1.showCoordinates() << endl;

    cout << "\nZad 9\n";
    cout << "R2: " << r2.showCoordinates() << endl;

    cout << "\nZad 10-11\n";
    IntersectionResult result1;
    cout << "S z R1: " << endl;
    s1.Hit(r1, 0, std::numeric_limits<float>::infinity());

    IntersectionResult result2;
    cout << "S z R2: " << endl;
    s1.Hit(r2, 0, std::numeric_limits<float>::infinity());

    cout << "\nZad 12\n";
    IntersectionResult result3;
    cout << "S z R3: " << endl;
    s1.Hit(r3, 0, std::numeric_limits<float>::infinity());


    cout << "\nZad 13-14";
    IntersectionResult int_res = p1.Intersects(r2, 200);
    cout << "P1: " << p1.showCoordinates() << endl << "punkt przeciecia z r2:" << int_res.LPOINT.showCoordinates()
         << endl;

    cout << "\nZad 15\n";
    Vector pktA = *new Vector(0, 0, 0);
    Vector pktB = *new Vector(1, 0, 0);
    Vector pktC = *new Vector(0, 1, 0);
    Triangle t1 = *new Triangle(pktA, pktB, pktC, color3);

    cout << "Przypadek 1:\n";
    Vector pkt1 = *new Vector(-1, 0.5, 0);
    Vector pkt2 = *new Vector(1, 0.5, 0);
    Ray ray1 = *new Ray(pkt1, pkt2);

    t1.IntersectTriangle(ray1, pktA, pktB, pktC);

    cout << "Przypadek 2:\n";
    Vector pkt3 = *new Vector(2, -1, 0);
    Vector pkt4 = *new Vector(2, 2, 0);
    Ray ray2 = *new Ray(pkt3, pkt4);

    t1.IntersectTriangle(ray2, pktA, pktB, pktC);

    cout << "Przypadek 3:\n";
    Vector pkt5 = *new Vector(0, 0, -1);
    Vector pkt6 = *new Vector(0, 0, 1);
    Ray ray3 = *new Ray(pkt5, pkt6);

    t1.IntersectTriangle(ray3, pktA, pktB, pktC);

    cout << "\nZad 1\n";
    Intensity li1 = *new Intensity(0.2, 0.2, 0.2);
    Intensity li2 = *new Intensity(0.1, 0.1, 0.1);
    cout << li1 << ", " << li2 << endl;
    li1 += li2;
    cout << li1 << ", " << li2 << endl;
    li2 = li1 / 4;
    cout << li1 << ", " << li2 << endl;
    li1 *= 2;
    cout << li1 << ", " << li2 << endl;
    li1 /= 3;
    cout << li1 << ", " << li2 << endl;
}

//    Vector Up = *new Vector(0, 0, 1);
//    PerspectiveCamera pc1 = *new PerspectiveCamera(ray_point, spher_point, spher_point, parallel, Up, 2);
//    cout << "PC1: " <<pc1.showCoordinates() << endl;

//
//
//
//    Vector spher_point = *new Vector(10, 0, 0);
//    Vector spher_point2 = *new Vector(0, 0, 0);
//
//    Intensity color1 = *new Intensity(1,0,0);
//    Intensity color2 = *new Intensity(0,1,0);
//    Intensity color3 = *new Intensity(0,0,1);
//    Sphere s1 = *new Sphere(spher_point, 19, color1);
//    Sphere s2 = *new Sphere(spher_point2, 3, color3);
//
//
//    cout<<s1.showCoordinates()<<endl;
//    cout<<s1.getColor().getRed()<<endl;
//    cout<<s1.getColor().getGreen()<<endl;
//    cout<<s1.getColor().getBlue()<<endl;
//
//    // Create an image with given width and height
//    Image image(800, 800);
//
//    // Define the parameters for the camera
//    Vector cameraPosition(-100, 0, 0);  // Set the camera position
//    Vector lookAt(-190, 0, 0);  // Set the point to look at
//    Vector up(0, 0, 1);  // Set the up vector
//
//// Create a perspective camera
//    PerspectiveCamera cameraPersp(cameraPosition, lookAt, up, 90.0f, image.width, image.height);
//
//    Vector cameraPositionOrto(-50, 0, 0);  // Set the camera position
//    Vector lookAtOrto(-30, 0, 0);  // Set the point to look at
//    Ray kierunek = *new Ray(cameraPositionOrto, lookAtOrto);
//    Vector zwrot = kierunek.getDirection();
//    Vector prostopadly = kierunek.getDirection();
//    Vector upOrto = zwrot.findPerpendicularVector(prostopadly);
//    cout<<"prostopadly" <<zwrot.showCoordinates()<<endl;
//    cout<<"prostopadly" <<prostopadly.showCoordinates()<<endl;
//    cout<<"Up orto "<<upOrto.showCoordinates()<<endl;
// //   Vector upOrto(0, 0, 1);  // Set the up vector
//    float leftOrto = -100.0f;   // Set the left boundary of the view frustum
//    float rightOrto = 100.0f;   // Set the right boundary of the view frustum
//    float bottomOrto = -100.0f; // Set the bottom boundary of the view frustum
//    float topOrto = 100.0f;     // Set the top boundary of the view frustum
//// Create an orthographic camera
//    OrtogonalCamera cameraOrto(cameraPositionOrto, lookAtOrto, * new Vector(1,0,0), leftOrto, rightOrto, bottomOrto, topOrto, image.width, image.height);
//
//    cout<<zwrot.showCoordinates()<<endl;
//    //Vector normalPlane = *new Vector(1, 0, 0);  // w sina dal od kamery
//    Vector pointPlane = cameraPositionOrto;
//    if(zwrot.getX()>0) {
//        pointPlane.add(*new Vector(400, 0, 0));// rownolegle do kamery
//    }
//    else {
//        pointPlane.sub(*new Vector(400, 0, 0));// rownolegle do kamery
//    }
//    Plane p1 = *new Plane(zwrot, pointPlane, color2);
//
//    cout<<p1.showCoordinates()<<endl;
//    cout<<s1.showCoordinates()<<endl;
//
//    //tlo zielone bedzie
//    //cout<<p1.showCoordinates()<<endl;
////    Vector ray_point = *new Vector(0, 0, -20);
////    Ray r1 = *new Ray(ray_point, spher_point);
//
//    // kastuje reje z kazdAego vertexa z image i one leca rownolegle i sprawdzam czy cos trafiaja
//    Vector pkt3 = *new Vector(2, -1, 0);
//    Vector pkt4 = *new Vector(2, 2, 0);
//    Ray ray = *new Ray(pkt3, pkt4);
////    for (int i = 0; i < image.height; i++){
////        for (int j = 0; j < image.width; j++){
//////            image.setPixel(j, i, sf::Color::Red);
////
////            Vector pixel = *new Vector(j, i, 0);
////            ray.setOrigin(pixel);
////            Vector destination = *new Vector(j, i, 200);
////            ray.setDestination(destination);
////
////            IntersectionResult intersection = s1.Hit(ray, 0, std::numeric_limits<float>::infinity());
////
////            // Perform ray tracing calculations here...
////            // For demonstration, let's print the color of the pixel to the console
////            if (intersection.type == HIT){
//////                cout<<s1.getColor().getRed()<<endl;
//////                cout<<s1.getColor().getGreen()<<endl;
//////                cout<<s1.getColor().getBlue()<<endl;
////                image.setPixel(j, i, s1.getColor());    //s1.getColor to typ intensity
////            }else{
////                Intensity bg = *new Intensity (0, 1, 1); //tlo na cyjan
////                image.setPixel(j, i, bg); //todo: trzeba ten kolor zmienic zeby go ie brac z s1 tylko z intersection result
////
////            }
////        }
////    }
//    Ray rayOrthographic = *new Ray(cameraPositionOrto,lookAtOrto);
//    // Iterate over each pixel in the image
//    for (int y = 0; y < image.height; ++y) {
//        for (int x = 0; x < image.width; ++x) {
//            // Cast a ray from the camera through the pixel
////            Ray rayPerspective = cameraPersp.castRay(x, y);
//
//            Ray kierunek = *new Ray(cameraPositionOrto, lookAtOrto);
//            float u = (-1.0f + 2.0f * x / (image.width - 1.0f)) * 20;
//            float v = (-1.0f + 2.0f * y / (image.height - 1.0f)) * 20;
//            Vector zwrot = kierunek.getDirection();
//            float cameraEnd = zwrot.getX();
//
//            Vector finish = *new Vector(cameraEnd, v, u);
//            float cameraPoint = cameraPositionOrto.getX();
//            Vector start = *new Vector(cameraPoint, v, u);
////            Vector start = rayOrthographic.getDirection();
////            cout<<start.showCoordinates()<<endl;
////            cout<<finish.showCoordinates()<<endl;
//
//
//            Ray rayOrthographic = *new Ray(start, finish);
//            // Check for intersections with the sphere
////            IntersectionResult intersectionPerspective = s1.Hit(rayPerspective, 0, std::numeric_limits<float>::infinity());
//            IntersectionResult intersectionOrthographic = s1.Hit(rayOrthographic, 0, 900);  //tmax to ten nasz far plane
//            IntersectionResult intersectionOrthographicS2 = s2.Hit(rayOrthographic, 0,
//                                                                   900);  //tmax to ten nasz far plane
//
//            IntersectionResult intersectionFarPlane = p1.Intersects(rayOrthographic, 0.0f);
//            // Set the pixel color based on the intersection result
////            if (intersectionPerspective.type == HIT) {
////                image.setPixel(x, y, intersectionPerspective.color);
////            } else
//            if (intersectionOrthographic.type == HIT) {
//                image.setPixel(x, y, intersectionOrthographic.color);
//            } else if (intersectionFarPlane.type == HIT || intersectionFarPlane.type == INSIDE_PRIMITIVE) {
//                image.setPixel(x, y, intersectionFarPlane.color);
//
//            } else {
//                // Set background color
//                Intensity bgColor(0, 0, 1);
//                image.setPixel(x, y, bgColor);
//            }
//            if (intersectionOrthographicS2.type == HIT) {
//                image.setPixel(x, y, intersectionOrthographicS2.color);
//            }
//        }
//    }
//    cout<<kierunek.showCoordinates()<<endl;
//    cout<<zwrot.showCoordinates()<<endl;
//    cout<<s1.showCoordinates()<<endl;
//    cout<<s2.showCoordinates()<<endl;
//    // Create SFML window
//
//    sf::RenderWindow window(sf::VideoMode(image.width, image.height), "SFML Image Test");
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
//
//
//}
