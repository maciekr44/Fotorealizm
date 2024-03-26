//
// Created by Kiu on 21.03.2024.
//

#include "Intensity.h"
#include <iostream>


Intensity::Intensity(): Intensity(0, 0, 0){}

Intensity::Intensity(float r, float g, float b)
{
    this->r = clip(r);
    this->g = clip(g);
    this->b = clip(b);
}


Intensity::~Intensity()
{
}

double Intensity::R()
{
    return r;
}

void Intensity::R(float value)
{
    r = clip(value);
}

double Intensity::G()
{
    return g;
}

void Intensity::G(float value)
{
    g = clip(value);
}

double Intensity::B()
{
    return b;
}

void Intensity::B(float value)
{
    b = clip(value);
}

void Intensity::add(double R, double G, double B)
{
    this->R(r + R);
    this->G(g + G);
    this->B(b + B);
}

void Intensity::operator()(float R, float G, float B)
{
    this->R(R);
    this->G(G);
    this->B(B);
}

void Intensity::operator()(float R, float G)
{
    this->R(R);
    this->G(G);
    this->b = 0;
}

void Intensity::operator()(float R)
{
    this->R(R);
    this->g = 0;
    this->b = 0;
}

Intensity Intensity::operator+(Intensity & li)
{
    return Intensity(r + li.R(), g + li.G(), b + li.B());
}

Intensity Intensity::operator-(Intensity & li)
{
    return Intensity(r - li.R(), g - li.G(), b - li.B());
}

Intensity Intensity::operator/(float num)
{
    if (num != 0) {
        return Intensity(r / num, g / num, b / num);
    }
    else {
        return Intensity(1, 1, 1);
        std::cout << "Dividin light intensity by 0\n";
    }
}

Intensity & Intensity::operator+=(Intensity & li)
{
    this->R(r + li.R());
    this->G(g + li.G());
    this->B(b + li.B());
    return *this;
}

Intensity & Intensity::operator-=(Intensity & li)
{
    this->R(r - li.R());
    this->G(g - li.G());
    this->B(b - li.B());
    return *this;
}

Intensity & Intensity::operator*=(float num)
{
    this->R(r * num);
    this->G(g * num);
    this->B(b * num);
    return *this;
}

Intensity & Intensity::operator/=(float num)
{
    if (num != 0) {
        this->R(r / num);
        this->G(g / num);
        this->B(b / num);
    }
    else {
        r = 1;
        g = 1;
        b = 1;
    }
    return *this;
}

std::ostream & operator<<(std::ostream & str, Intensity & li)
{
    str << "(R:" << li.R() << ", G:" << li.G() << ", B:" << li.B() << ")";
    return str;
}

sf::Color Intensity::intensityToSFMLColor() {

    // Convert each component from float (0-1) to int (0-255)
    int red = static_cast<int>(r * 255);
    int green = static_cast<int>(g * 255);
    int blue = static_cast<int>(b * 255);

    // Return sf::Color object with the converted RGB values
    return sf::Color(red, green, blue);
}
