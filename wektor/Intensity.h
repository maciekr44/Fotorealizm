#pragma once

#include <ostream>

class Intensity
{
public:
    Intensity();
    Intensity(float r, float g, float b);
    Intensity(float r, float g);
    Intensity(float r);

    ~Intensity();

    float R();
    void R(float value);
    float G();
    void G(float value);
    float B();
    void B(float value);

    void add(double R, double G, double B);

    void operator()(float R, float G, float B);
    void operator()(float R, float G);
    void operator()(float R);

    Intensity operator+(Intensity &li);
    Intensity operator-(Intensity &li);

    Intensity operator/(float num);

    Intensity& operator+=(Intensity &li);
    Intensity& operator-=(Intensity &li);

    Intensity& operator*=(float num);
    Intensity& operator/=(float num);

//    friend Intensity& operator*(float num, Intensity &li);
//    friend Intensity& operator*(Intensity &li, float num);
        friend std::ostream& operator<<(std::ostream& str, Intensity &li);

    float clamp01(float value)
    {
        float result = value;
        if (result < 0) {
            result = 0;
        }
        if (result > 1) {
            result = 1;
        }
        return result;
    }


protected:
    float r;
    float b;
    float g;
};

