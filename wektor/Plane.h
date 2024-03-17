//
// Created by Maciek on 13.03.2024.
//

#ifndef WEKTORY_PLANE_H
#define WEKTORY_PLANE_H


#include "Vector.h"
#include "IntersectionResult.h"

class Plane {
public:
    Plane(Vector normal_vector, Vector point); //plaszczyzne definiujemy za pomoca wektora i punktu (3 punkty zawierajace sie w plaszcyznie)

    Vector Normal_vector() const {return Normal_vector_;}
    Vector Point() const {return Point_;}

    const Vector &getNormalVector() const;
    void setNormalVector(const Vector &normalVector);

    const Vector &getPoint() const;
    void setPoint(const Vector &point);

    std::string showCoordinates() const;

    IntersectionResult Intersects(Ray ray, float range) const;

private:
    Vector Normal_vector_;
    Vector Point_;


};


#endif //WEKTORY_PLANE_H
