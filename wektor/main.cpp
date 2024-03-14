#include <iostream>
#include <string>
#include "Vector.h"
//egrsrbh TATASSS titis TOTOS and boobas and cock
using namespace std;

float angle(Vector v1, Vector v2) {
    return acos(v1.dotProduct(v2) / (v1.length() * v2.length())) * 180 / M_PI;
}

int main() {
    Vector w1 = *new Vector(1, 2, 3);
    Vector w2 = *new Vector(4, 5, 6);
    Vector w3 = *new Vector(0, 3, 0);
    Vector w4 = *new Vector(5, 5, 0);
    Vector w5 = *new Vector(4, 5, 1);
    Vector w6 = *new Vector(4, 1, 3);

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

    return 0;
}
