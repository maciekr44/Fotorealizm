//#include "Geometry.h"

class OrtogonalCamera {
public:
    Vector positionOrto;
    Vector lookAtOrto;
    Vector upOrto;

public:

    OrtogonalCamera(Vector positionOrto, Vector lookAtOrto, Vector upOrto) : positionOrto(
            positionOrto), lookAtOrto(lookAtOrto), upOrto(upOrto) {}

    static Material antyaliasingOrto(int sampling, float antialiasingPixelX, float antialiasingPixelY, float antialiasingPixelSize, Ray raySampling, std::list<Geometry*> objects, Ray rayOrthographic){
        int iterator = 0;
        IntersectionResult closestIntersection;
        Material Colors[sampling * sampling];
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
                Colors[iterator] = closestIntersection.material;
                iterator++;


            }
        }
        Material meanColor;
        Vector colorsVector(0, 0, 0);
        Vector sum(0, 0, 0);
        for(int s = 0; s<sampling*sampling; ++s){
            meanColor = Colors[s];
            colorsVector.setX(meanColor.diffuse_colour.getRed());
            colorsVector.setY(meanColor.diffuse_colour.getGreen());
            colorsVector.setZ(meanColor.diffuse_colour.getBlue());

            sum.add(colorsVector);

        }
        sum.div(sampling * sampling);

        meanColor.diffuse_colour.R(sum.getX());
        meanColor.diffuse_colour.G(sum.getY());
        meanColor.diffuse_colour.B(sum.getZ());

        return (meanColor);
    }

    static Vector closestIntersection(int sampling, float antialiasingPixelX, float antialiasingPixelY, float antialiasingPixelSize, Ray raySampling, std::list<Geometry*> objects, Ray rayOrthographic) {
        int iterator = 0;
        IntersectionResult closestIntersection;
        Material Colors[sampling * sampling];
        for (int t = 0; t < sampling; ++t) {
            for (int p = 0; p < sampling; ++p) {
                Vector samplingOrigin(0, antialiasingPixelX + (antialiasingPixelSize * t),
                                      antialiasingPixelY + (antialiasingPixelSize * p));
                raySampling.setOrigin(samplingOrigin);
                Vector samplingDestination(100, antialiasingPixelX + (antialiasingPixelSize * t),
                                           antialiasingPixelY + (antialiasingPixelSize * p));
                raySampling.setDestination(samplingDestination);

                closestIntersection.distance = std::numeric_limits<float>::infinity(); // jak tu jest nieskonczonosc to jakikolwiek hit bedzie mniejszy

                for (auto obj: objects) {  //jednym z obiektow winien byc farplane
                    IntersectionResult intersection = obj->collision(raySampling, 0, 1000);
                    if (intersection.type == HIT && intersection.distance < closestIntersection.distance) {
                        closestIntersection = intersection;
                        Vector distance = closestIntersection.LPOINT;
//                        std::cout<<distance.showCoordinates()<<std::endl;
                        return distance;
                    }
                }
                Colors[iterator] = closestIntersection.material;
                iterator++;


            }
        }
    }
};