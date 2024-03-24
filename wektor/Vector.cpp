//
// Created by mical on 02.11.2022.
//


#include "Vector.h"

using namespace std;

Vector::Vector() {
    setX(0);
    setY(0);
    setZ(0);
}

Vector::Vector(float x, float y, float z) : x(x), y(y), z(z) {}

Vector::~Vector() {
}

float Vector::getX() const {
    return x;
}

void Vector::setX(float x) {
    Vector::x = x;
}

float Vector::getY() const {
    return y;
}

void Vector::setY(float y) {
    Vector::y = y;
}

float Vector::getZ() const {
    return z;
}

void Vector::setZ(float z) {
    Vector::z = z;
}

string Vector::showCoordinates() const {
    return string("[") + to_string(getX()) + string(", ") + to_string(getY()) + string(", ") +
           to_string(getZ()) + string("]");
}

void Vector::add(Vector v) {
    setX(getX() + v.getX());
    setY(getY() + v.getY());
    setZ(getZ() + v.getZ());
}

void Vector::sub(Vector v) {
    setX(getX() - v.getX());
    setY(getY() - v.getY());
    setZ(getZ() - v.getZ());
}

void Vector::mag(float r) {
    setX(getX() * r);
    setY(getY() * r);
    setZ(getZ() * r);
}

void Vector::div(float n) {
    if (n != 0) {
        setX(getX() / n);
        setY(getY() / n);
        setZ(getZ() / n);
    } else cout << "Can't divide by 0 [Div]" << endl;
}

float Vector::length() {
    return sqrtf(powf(getX(), 2) + powf(getY(), 2) + powf(getZ(), 2));
}

Vector Vector::abs(Vector v) {
    return Vector(fabs(x), fabs(y), fabs(z));
}

void Vector::normalize() {
    float n = this->length();
    if (n != 0) this->div(n);
    else cout << "Can't divide by 0 [Normalize]" << endl;
}

Vector Vector::dot(Vector v) {
    Vector vector;
    vector.setX(getX() * v.getX());
    vector.setY(getY() * v.getY());
    vector.setZ(getZ() * v.getZ());
    return vector;
}

float Vector::dotProduct(Vector v) {
    return getX() * v.getX() + getY() * v.getY() + getZ() * v.getZ();
}

Vector Vector::cross(Vector v) {
    Vector vector;
    vector.setX(getY() * v.getZ() - getZ() * v.getY());
    vector.setY(getZ() * v.getX() - getX() * v.getZ());
    vector.setZ(getX() * v.getY() - getY() * v.getX());
    return vector;
}

std::ostream& operator<<(std::ostream& os, const Vector& v) {
    os << "(" << v.getX() << ", " << v.getY() << ", " << v.getZ() << ")";
    return os;
}

Vector Vector::findPerpendicularVector(Vector v) {
    // Wyznaczamy wektor prostopadły do v poprzez przeprowadzenie iloczynu wektorowego
    // z dowolnym wektorem różnym od v.

    // Wybieramy wektor różny od v, który nie jest równoległy do niego
    Vector arbitraryVector;
    if (v.getX() != 0 || v.getY() != 0) {
        arbitraryVector = Vector(v.getZ(), 0, -v.getX());
    } else {
        arbitraryVector = Vector(0, v.getZ(), -v.getY());
    }
    v.cross(arbitraryVector);
    v.normalize();
    // Obliczamy iloczyn wektorowy\
    Vector perpendicularVector = v.cross(arbitraryVector);

    // Zwracamy znormalizowany wektor prostopadły
    return v;
}

