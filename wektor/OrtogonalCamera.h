#include "Vector.h"

class OrtogonalCamera {
public:
    Vector positionOrto;
    Vector lookAtOrto;
    Vector upOrto;

public:

    OrtogonalCamera(Vector positionOrto, Vector lookAtOrto, Vector upOrto) : positionOrto(
            positionOrto), lookAtOrto(lookAtOrto), upOrto(upOrto) {}

    static Intensity antyaliasingOrto(int sampling, float antialiasingPixelX, float antialiasingPixelY, float antialiasingPixelSize, Ray raySampling, Sphere s1, Sphere s2, Ray rayOrthographic){
        int iterator = 0;
        Intensity Colors[sampling * sampling];
        for(int t = 0; t<sampling; ++t){
            for(int p = 0; p<sampling; ++p){
                Vector samplingOrigin(0, antialiasingPixelX + (antialiasingPixelSize * t), antialiasingPixelY + (antialiasingPixelSize * p));
                raySampling.setOrigin(samplingOrigin);
                Vector samplingDestination(100, antialiasingPixelX + (antialiasingPixelSize * t), antialiasingPixelY + (antialiasingPixelSize * p));
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