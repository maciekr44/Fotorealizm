#include "Vector.h"
#include "Ray.h"
#include "Intensity.h"
#include "Sphere.h"


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

    static Intensity antyaliasingPersp(int sampling, float antialiasingPixelX, float antialiasingPixelY, float antialiasingPixelSize, Ray raySampling, Sphere s1, Sphere s2, Ray rayOrthographic){
        int iterator = 0;
        Intensity Colors[sampling * sampling];
        for(int t = 0; t<sampling; ++t){
            for(int p = 0; p<sampling; ++p){

                Vector samplingDestination(0, antialiasingPixelX + (antialiasingPixelSize * t), antialiasingPixelY + (antialiasingPixelSize * p));
                raySampling.setDestination(samplingDestination);
                // Check for intersections with the sphere
                IntersectionResult intersectionOrthographic = s1.Hit(raySampling, 0, 900);  //tmax to ten nasz far plane
                IntersectionResult intersectionOrthographicS2 = s2.Hit(raySampling, 0,
                                                                       900);  //tmax to ten nasz far plane


                if (intersectionOrthographic.type == HIT && intersectionOrthographicS2.type != HIT) {
                    Colors[iterator] = intersectionOrthographic.color;
                } else if (intersectionOrthographicS2.type == HIT && intersectionOrthographic.type != HIT) {
                    Colors[iterator] = intersectionOrthographicS2.color;
                } else if (intersectionOrthographic.type == HIT && intersectionOrthographicS2.type == HIT) {
                    // Choose the closest intersection
                    if (intersectionOrthographic.distance < intersectionOrthographicS2.distance) {
                        Colors[iterator] = intersectionOrthographic.color;
                    } else {
                        Colors[iterator] = intersectionOrthographicS2.color;
                    }
                } else {
                    // Set background color
                    Intensity bgColor(0, 0.1, 0.1);
                    Colors[iterator] = bgColor;
                }
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
