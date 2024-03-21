//
// Created by Kiu on 21.03.2024.
//

#ifndef WEKTORY_INTENSITY_H
#define WEKTORY_INTENSITY_H

#include <ostream>

using namespace std;

class Intensity
{
protected:
    double r, g, b;
public:
    Intensity(double R, double G, double B){ r=R; g=G; b=B;}
    Intensity(double R, double G){ r=R; g=G; b=0.0;}
    Intensity(double R){ r=R; g=b=0.0;}
    Intensity(){r=g=b=0.0;}
    double getRed() {return r;}
    double getGreen() {return g;}
    double getBlue() {return b;}
    void operator()(float R, float G, float B) { r=R; g=G; b=B;}
    void operator()(float R, float G) { r=R; g=G; b=0.0;}
    void operator()(float R) { r=R; g=b=0.0;}

    void add(double R, double G, double B);

    Intensity operator+(Intensity &li);
    Intensity operator-(Intensity &li);
    Intensity operator/(float num);
    void operator+=(Intensity &li);
    Intensity operator-=(Intensity &li);
    Intensity operator*=(float num);
    Intensity operator/=(float num);
    friend Intensity operator*(float num, Intensity &li);
    friend Intensity operator*(Intensity &li, float num);
//    friend ostream& operator<<(ostream& str, Intensity &li);
};

#endif //WEKTORY_INTENSITY_H
