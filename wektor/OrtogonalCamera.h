//#include "Geometry.h"

class OrtogonalCamera {
public:
    Vector positionOrto;
    Vector lookAtOrto;
    Vector upOrto;

public:

    OrtogonalCamera(Vector positionOrto, Vector lookAtOrto, Vector upOrto) : positionOrto(
            positionOrto), lookAtOrto(lookAtOrto), upOrto(upOrto) {}

    static Intensity antyaliasingOrto(int sampling, float antialiasingPixelX, float antialiasingPixelY, float antialiasingPixelSize, Ray raySampling, std::list<Geometry*> objects, Ray rayOrthographic){
        int iterator = 0;
        IntersectionResult closestIntersection;
        Intensity Colors[sampling * sampling];
        for(int t = 0; t<sampling; ++t){
            for(int p = 0; p<sampling; ++p){
                Vector samplingOrigin(0, antialiasingPixelX + (antialiasingPixelSize * t), antialiasingPixelY + (antialiasingPixelSize * p));
                raySampling.setOrigin(samplingOrigin);
                Vector samplingDestination(100, antialiasingPixelX + (antialiasingPixelSize * t), antialiasingPixelY + (antialiasingPixelSize * p));
                raySampling.setDestination(samplingDestination);

                closestIntersection.distance = std::numeric_limits<float>::infinity(); // jak tu jest nieskonczonosc to jakikolwiek hit bedzie mniejszy

                for (auto obj : objects) {  //jednym z obiektow winien byc farplane
                    IntersectionResult intersection = obj->collision(raySampling, 0, 1000);
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