//
// Created by Kiu on 21.03.2024.
//

#include "Intensity.h"
#include <math.h>
#include <iostream>

float clamp01(float value);

Intensity::Intensity(): Intensity(0, 0, 0){}

Intensity::Intensity(float r, float g, float b)
{
    this->r = clamp01(r);
    this->g = clamp01(g);
    this->b = clamp01(b);
}

Intensity::Intensity(float r, float g) : Intensity(r, g, 0){}

Intensity::Intensity(float r) : Intensity(r, 0, 0) {}


Intensity::~Intensity()
{
}

float Intensity::R()
{
    return r;
}

void Intensity::R(float value)
{
    r = clamp01(value);
}

float Intensity::G()
{
    return g;
}

void Intensity::G(float value)
{
    g = clamp01(value);
}

float Intensity::B()
{
    return b;
}

void Intensity::B(float value)
{
    b = clamp01(value);
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

//Intensity operator (float num, Intensity & li)
//{
//    return Intensity(li.R() * num, li.G() * num, li.B() * num);
//}
//
//Intensity & operator*(Intensity & li, float num)
//{
//    return Intensity(li.R() * num, li.G() * num, li.B() * num);
//}

std::ostream & operator<<(std::ostream & str, Intensity & li)
{
    str << "(R:" << li.R() << ", G:" << li.G() << ", B:" << li.B() << ")";
    return str;
}
