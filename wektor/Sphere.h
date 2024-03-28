//
// Created by Maciek on 13.03.2024.
//

#ifndef WEKTORY_SPHERE_H
#define WEKTORY_SPHERE_H
#include "Geometry.h"

//#include "IntersectionResult.h"

class Sphere : public Geometry{
    public:
        Sphere();
        Sphere(Vector v, float r, Intensity color);

        IntersectionResult collision(Ray ray, float t_min, float t_max) const;

        Vector Center() const { return Center_; }
        void Center(Vector o) { Center_ = o; }
        float Radius() const { return Radius_;}
        void Radius(float r) {Radius_ = r;}

        friend std::ostream& operator <<(std::ostream& os, const Sphere& sph);

        Vector getCenter() const;
        void setCenter(Vector center);

        float getRadius() const;
        void setRadius(float radius);

        Intensity getColor();
        void setColor(Intensity color);

        std::string showCoordinates() const;

        virtual ~Sphere();
        Intensity Color_;


        Vector Center_;
        float Radius_;


};


#endif //WEKTORY_SPHERE_H
