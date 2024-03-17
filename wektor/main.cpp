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

//Vector Vector::list(Vector s, Vector r) {
//    std::pair<bool, std::pair<Vector, Vector>> result;
//    result = s.Hit(r, 0, std::numeric_limits<float>::infinity());
//    if (result.first) {
//        cout << "Kolizja!" << endl;
//        Vector hit_point = result.second.second; // Punkt kolizji
//        cout << hit_point.showCoordinates() << endl;
//        return hit_point;
//    } else {
//        cout << "Brak kolizji." << endl;
//    }
//
//}


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

    Vector ray_point = *new Vector(0, 0, -20);
    Ray r1 = *new Ray(ray_point, spher_point);

    Vector parallel = *new Vector(0, 20, -20);
    Ray r2 = *new Ray(ray_point, parallel);

    Vector third_origin = *new Vector(8, -12, 0);
    Vector third_destination = *new Vector(3, -2, 0);
    Ray r3 = *new Ray(third_origin, third_destination);

    Vector angle45 = *new Vector(0, 1, 1);
    Plane p1 = *new Plane(angle45, spher_point);

    cout << "\nZad 1\n" <<endl;
    cout << "Zaimplementowalismy klase wektor wraz ze wszystkimi dzialaniami." <<endl;

    cout << "\nZad 2\n" <<endl;
    cout << "V1: " <<w1.showCoordinates() << endl;
    cout << "V2: " <<w2.showCoordinates() << endl;
    w1.add(w2);

    cout <<"Suma wektorow:"<<endl;
    cout <<"V1 + V2 = "<< w1.showCoordinates() << endl;

    w1.sub(w2);
    w2.add(w1);
    cout <<"V2 + V1 = "<< w2.showCoordinates() << endl;


    cout << "\nZad 3\n" << "V1: " << w3.showCoordinates() << "\nV2: " << w4.showCoordinates() << endl;
    cout << "Kat wynosi: " << to_string(angle(w3, w4)) <<" stopni"<< endl;

    cout << "\nZad 4\n" << "V1: " << w5.showCoordinates() << "\nV2: " << w6.showCoordinates() << endl;
    Vector prostopadly = w5.cross(w6);
    cout << "Wektor prostopadly do obu poprzednich ma wspolrzedne: " << prostopadly.showCoordinates() << endl;

    cout << "\nZad 5\n";
    prostopadly.normalize();
    cout << "Znormalizowany poprzedni wektor prostopadly ma wspolrzedne: " << prostopadly.showCoordinates() << endl;

    cout << "\nZad 6\n";
    cout << "Zaimplementowalismy klasy promien, sfera i plaszczyzna." << endl;

    cout << "\nZad 7\n";
    cout << "S1: " <<s1.showCoordinates() << endl;

    cout << "\nZad 8\n";
    cout << "R1: " <<r1.showCoordinates() << endl;

    cout << "\nZad 9\n";
    cout << "R2: " <<r2.showCoordinates() << endl;

    cout << "\nZad3131\n" << endl;
    cout << "Kat wynosi: " << to_string(direction_angle(w90)) <<" stopni"<< endl;

    cout << "\nZad 10-11\n";
    Vector result1;
    cout << "S z R1: " << endl;
    result1 = s1.Hit(r1, 0, std::numeric_limits<float>::infinity());


    Vector result2;
    cout << "S z R2: " << endl;
    result2 = s1.Hit(r2, 0, std::numeric_limits<float>::infinity());


    cout << "\nZad 12\n";
    Vector result3;
    cout << "S z R3: "  << endl;
    result3 = s1.Hit(r3, 0, std::numeric_limits<float>::infinity());

    cout << "\nZad 13\n";
    cout << "P1: " <<p1.showCoordinates() << endl;


}
