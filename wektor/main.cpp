#include <iostream>
#include <string>
#include <limits>
#include "Vector.h"
#include "Sphere.h"
#include "Ray.h"
#include "Plane.h"
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

    Vector spher_point = *new Vector(0, 0, 0);
    Sphere s1 = *new Sphere(spher_point, 10);

    Vector ray_point = *new Vector(0, 11, 0);
    Ray r1 = *new Ray(ray_point, spher_point);

    Vector parallel = *new Vector(0, 20, -20);
    Ray r2 = *new Ray(ray_point, parallel);

    cout << "\nZad1\n" <<endl;
    cout << "Zaimplementowalismy klase wektor wraz ze wszystkimi dzialaniami." <<endl;

    cout << "\nZad2\n" <<endl;
    cout << "V1: " <<w1.showCoordinates() << endl;
    cout << "V2: " <<w2.showCoordinates() << endl;
    w1.add(w2);

    cout <<"Suma wektorow:"<<endl;
    cout <<"V1 + V2 = "<< w1.showCoordinates() << endl;

    w1.sub(w2);
    w2.add(w1);
    cout <<"V2 + V1 = "<< w2.showCoordinates() << endl;


    cout << "\nZad3\n" << "V1: " << w3.showCoordinates() << "\nV2: " << w4.showCoordinates() << endl;
    cout << "Kat wynosi: " << to_string(angle(w3, w4)) <<" stopni"<< endl;

    cout << "\nZad4\n" << "V1: " << w5.showCoordinates() << "\nV2: " << w6.showCoordinates() << endl;
    Vector prostopadly = w5.cross(w6);
    cout << "Wektor prostopadly do obu poprzednich ma wspolrzedne: " << prostopadly.showCoordinates() << endl;

    cout << "\nZad5\n";
    prostopadly.normalize();
    cout << "Znormalizowany poprzedni wektor prostopadly ma wspolrzedne: " << prostopadly.showCoordinates() << endl;

    cout << "\nZad6\n";
    cout << "Zaimplementowalismy klasy promien, sfera i plaszczyzna." << endl;

    cout << "\nZad7\n";
    cout << "S1: " <<s1.showCoordinates() << endl;

    cout << "\nZad8\n";
    cout << "R1: " <<r1.showCoordinates() << endl;

    cout << "\nZad9\n";
    cout << "R2: " <<r2.showCoordinates() << endl;

    cout << "\nZad3131\n" << endl;
    cout << "Kat wynosi: " << to_string(direction_angle(w90)) <<" stopni"<< endl;

    cout << "\nZad10\n";
    cout << "S z R1: " <<s1.Hit(r1, 0, numeric_limits<float>::infinity()) << endl;
    cout << "S z R2: " <<s1.Hit(r2,0, numeric_limits<float>::infinity()) << endl;
    cout << "^^to nie dziala^^"  << endl;
}
