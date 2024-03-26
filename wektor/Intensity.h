#pragma once

#include <ostream>
#include <Graphics/Color.hpp>

class Intensity
{
public:
    Intensity();
    Intensity(float r, float g, float b);

    ~Intensity();

    double R();
    void R(float value);
    double G();
    void G(float value);
    double B();
    void B(float value);

    double getRed() {return r;}
    double getGreen() {return g;}
    double getBlue() {return b;}

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

    sf::Color intensityToSFMLColor();

        friend std::ostream& operator<<(std::ostream& str, Intensity &li);

    float clip(float value)
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

