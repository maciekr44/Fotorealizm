//
// Created by mical on 02.11.2022.
//

#ifndef WEKTORY_VECTOR_H
#define WEKTORY_VECTOR_H

#include <iostream>
#include <cmath>
#include <string>

class Vector {
private:
    float x, y, z;

public:
    // Constructors
    Vector();

    Vector(float x, float y, float z);

    virtual ~Vector();

    // Getters and setters
    float getX() const;

    void setX(float x);

    float getY() const;

    void setY(float y);

    float getZ() const;

    void setZ(float z);

    // Functions
    std::string showCoordinates() const;

    void add(Vector v);

    void sub(Vector v);

    void mag(float r);

    void div(float n);

    float length();

    void normalize();

    Vector dot(Vector v);

    float dotProduct(Vector v);

    Vector cross(Vector v);


};


#endif //WEKTORY_VECTOR_H
