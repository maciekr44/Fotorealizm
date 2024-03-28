#include "Geometry.h"
#include <list>


class PerspectiveCamera {
private:
    Vector position;
    Vector lookAt;
    Vector up;
    float fov;

public:
    PerspectiveCamera(Vector position, Vector lookAt, Vector up, float fov) : position(position), lookAt(lookAt), up(up), fov(fov){}
    
    // Calculate the right vector based on the up vector and the direction from camera position to lookAt
    Vector right() const {
        Vector direction = lookAt;
        direction.sub(position);
        Vector right = direction.cross(up);
        return right;
    }

    static Intensity antyaliasingPersp(int sampling, float antialiasingPixelX, float antialiasingPixelY, float antialiasingPixelSize, Ray raySampling, std::list<Geometry*> objects, Ray rayOrthographic){
        int iterator = 0;
        IntersectionResult closestIntersection;
        Intensity Colors[sampling * sampling];
        for(int t = 0; t<sampling; ++t){
            for(int p = 0; p<sampling; ++p){

                Vector samplingDestination(0, antialiasingPixelX + (antialiasingPixelSize * t), antialiasingPixelY + (antialiasingPixelSize * p));
                raySampling.setDestination(samplingDestination);
                // Check for intersections with the sphere

                closestIntersection.distance = std::numeric_limits<float>::infinity(); // jak tu jest nieskonczonosc to jakikolwiek hit bedzie mniejszy

                for (auto obj : objects) {  //jednym z obiektow winien byc farplane
                    IntersectionResult intersection = obj->collision(raySampling, 0, 900);
                    if (intersection.type == HIT && intersection.distance < closestIntersection.distance) {
                        closestIntersection = intersection;
                    }
                }
                Colors[iterator] = closestIntersection.color;
                iterator++;


            }
        }
        Intensity meanColor;
        Vector colorsVector(0, 0, 0);
        Vector sum(0, 0, 0);
        for(int s = 0; s<sampling*sampling; ++s){
            meanColor = Colors[s];
            colorsVector.setX(meanColor.getRed());
            colorsVector.setY(meanColor.getGreen());
            colorsVector.setZ(meanColor.getBlue());

            sum.add(colorsVector);


        }

        sum.div(sampling * sampling);

        meanColor.R(sum.getX());
        meanColor.G(sum.getY());
        meanColor.B(sum.getZ());

        return (meanColor);

    }
};
