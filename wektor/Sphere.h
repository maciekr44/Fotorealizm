//
// Created by Maciek on 13.03.2024.
//

#ifndef WEKTORY_SPHERE_H
#define WEKTORY_SPHERE_H
#include "Vector.h"
#include "Ray.h"

class Sphere {
    public:
        Sphere(Vector v, float r);

        Vector Hit(Ray ray, float t_min, float t_max) const;

        Vector Center() const { return Center_; }
        void Center(Vector o) { Center_ = o; }
        float Radius() const { return Radius_;}
        void Radius(float r) {Radius_ = r;}

        friend std::ostream& operator <<(std::ostream& os, const Sphere& sph);

    Vector getCenter() const;
    void setCenter(Vector center);

    float getRadius() const;
    void setRadius(float radius);

    std::string showCoordinates() const;

    virtual ~Sphere();

private:
        Vector Center_;
        float Radius_;
};


#endif //WEKTORY_SPHERE_H
