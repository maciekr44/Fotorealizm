//
// Created by Kiu on 21.03.2024.
//

#include "Intensity.h"
#include "PointLight.h"
#include "Ray.h"
#include <iostream>
using namespace std;


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
Intensity Intensity::operator*(Intensity & li)
{
    return Intensity(r * li.R(), g * li.G(), b * li.B());
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

Vector Intensity::calculateIntensity(PointLight pointLight, Vector Op) {
    Ray distance(pointLight.location, Op);
    float I = 1.0 / (pointLight.constAtten + (pointLight.linearAtten * abs(distance.getDistance())));
    Vector In(I, I, I);
//    cout<<I.showCoordinates()<<endl;
    return In;
}

Vector Intensity::isInShadow(PointLight pointLight, Vector Op) {
    Vector In(1, 0, 1);
//    cout<<I.showCoordinates()<<endl;
    return In;
}

Intensity calculatePhong(Vector cameraPosition, IntersectionResult result, PointLight light, bool inShadow) {
    // Compute ambient component (usually a fraction of the object's color)
    Intensity ambientColor = result.material.color;

    // calculate distance:
    Ray distanceRay(result.LPOINT, light.location);
    float distance = distanceRay.getDistance();
    cout << distance << endl;


    // Calculate attenuation
    float attenuation = 1.0f / (light.constAtten + light.linearAtten * distance + light.quadAtten * distance * distance);
    // Apply attenuation to the actual color of the light
    Intensity intensity = light.color * attenuation;

    // Compute diffuse component
    Vector lightDirectionTMP = light.location;
    lightDirectionTMP.sub(result.LPOINT);
    Vector lightDirection = lightDirectionTMP;
    lightDirection.normalize();
    float diffuseFactor = std::max(0.0f, result.intersectionLPOINTNormal.dotProduct(lightDirection));
    Intensity diffuseColor = intensity * result.material.diffuse_colour * diffuseFactor;

    // Compute reflection vector and specular component
    Vector reflection = 2 * result.intersectionLPOINTNormal.dotProduct(lightDirection) * result.intersectionLPOINTNormal - lightDirection;
    reflection.normalize();
    Vector viewDirection = cameraPosition - result.LPOINT;
    viewDirection.normalize();
    float specularFactor = std::pow(std::max(0.0f, reflection.dotProduct(viewDirection)), result.material.shininess);
    Intensity specularColor = intensity * result.material.specular_colour * specularFactor;

    // Check for shadow and adjust components if necessary
    if (inShadow) {
        diffuseColor = Intensity(); // Set diffuse color to black or attenuate it
        specularColor = Intensity(); // Set specular color to black or attenuate it
    }

    // Combine components to get final pixel color
    return ambientColor + diffuseColor + specularColor;
}
