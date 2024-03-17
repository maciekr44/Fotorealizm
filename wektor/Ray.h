//
// Created by Maciek on 13.03.2024.
//

#ifndef WEKTORY_RAY_H
#define WEKTORY_RAY_H


#include "Vector.h"

class Ray {
public:

    Ray(Vector origin, Vector destination);


    Vector Origin() const {return Origin_;}
    void Origin(Vector o) {Origin_ =o;}
    Vector Destination() const {return Destination_;}
    void Destination(Vector d) {Destination_=d;}
    Vector Direction() const {return Direction_;}
    void Direction(Vector d) {Direction_=d;}
    float Distance() const {return Distance_;}
    void Distance(float d) {Distance_=d;}

    friend std::ostream& operator<<(std::ostream& os, const Ray& ray);

    const Vector &getOrigin() const;
    void setOrigin(const Vector &origin);

    const Vector &getDestination() const;
    void setDestination(const Vector &destination);

    const Vector &getDirection() const;
    void setDirection(const Vector &direction);

    float getDistance();
    void setDistance(float distance);

    std::string showCoordinates();

private:
    Vector Origin_;
    Vector Destination_;
    Vector Direction_;
    float Distance_;

};


#endif //WEKTORY_RAY_H
