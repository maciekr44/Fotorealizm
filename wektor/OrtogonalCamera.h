#include "Vector.h"

class OrtogonalCamera {
public:
    Vector positionOrto;
    Vector lookAtOrto;
    Vector upOrto;
    float leftOrto;
    float rightOrto;
    float bottomOrto;
    float topOrto;
    int widthOrto;
    int heightOrto;

public:

    OrtogonalCamera(const Vector &positionOrto, const Vector &lookAtOrto, const Vector &upOrto) : positionOrto(
            positionOrto), lookAtOrto(lookAtOrto), upOrto(upOrto) {}

    static Intensity antyaliasingOrto(int sampling, float pointV, float pointU, float szerokosc, Ray raySampling, Sphere s1, Sphere s2, Ray rayOrthographic,  int iterator){

        Intensity Kolory[sampling*sampling];
        for(int t = 0; t<sampling; ++t){
            // todo: po co to skoro nizej i tak nadpisuje??
//                Vector samplingOrigin(0,pointV+(szerokosc*t),pointU);
//                raySampling.setOrigin(samplingOrigin);
//                Vector samplingDestination(100,pointV+(szerokosc*t),pointU);
//                raySampling.setDestination(samplingDestination);
            for(int p = 0; p<sampling; ++p){
                Vector samplingOrigin(0,pointV+(szerokosc*t),pointU+(szerokosc*p));
                raySampling.setOrigin(samplingOrigin);
                Vector samplingDestination(100,pointV+(szerokosc*t),pointU+(szerokosc*p));
                raySampling.setDestination(samplingDestination);

//                std::cout << raySampling.showCoordinates() << std::endl;

                // Check for intersections with the sphere
                IntersectionResult intersectionOrthographic = s1.Hit(raySampling, 0, 900);  //tmax to ten nasz far plane
                IntersectionResult intersectionOrthographicS2 = s2.Hit(raySampling, 0,
                                                                       900);  //tmax to ten nasz far plane


                if (intersectionOrthographic.type == HIT && intersectionOrthographicS2.type != HIT) {
                    Kolory[iterator] = intersectionOrthographic.color;
                } else if (intersectionOrthographicS2.type == HIT && intersectionOrthographic.type != HIT) {
                    Kolory[iterator] = intersectionOrthographicS2.color;
                } else if (intersectionOrthographic.type == HIT && intersectionOrthographicS2.type == HIT) {
                    // Choose the closest intersection
                    if (intersectionOrthographic.distance < intersectionOrthographicS2.distance) {
                        Kolory[iterator] = intersectionOrthographic.color;
                    } else {
                        Kolory[iterator] = intersectionOrthographicS2.color;
                    }
                } else {
                    // Set background color
                    Intensity bgColor(0, 1, 1);
                    Kolory[iterator] = bgColor;
                }

//                if (Kolory[iterator].getRed() != 0 && Kolory[iterator].getGreen() != 1 && Kolory[iterator].getBlue() != 1)
//                std::cout << Kolory[iterator].getRed() << "; " << Kolory[iterator].getGreen() << "; "  << Kolory[iterator].getBlue() << std::endl;
                iterator++; // wychodzi na to ze dotad kolory sa poprawnie


            }
        }
        Intensity sredni;
        Vector kolorki(0,0,0);
        Vector suma(0,0,0);
        for(int s = 0; s<sampling*sampling; ++s){
            sredni = Kolory[s];
            kolorki.setX(sredni.getRed());
            kolorki.setY(sredni.getGreen());
            kolorki.setZ(sredni.getBlue());

//            std::cout << kolorki.showCoordinates() << std::endl;

            suma.add(kolorki);


        }
//        std::cout << suma.getX() << "; " << suma.getY() << "; "  << suma.getZ() << std::endl;

        suma.div(sampling*sampling);


//        std::cout << "po normlaizacjiajcsiq: " << suma.getX() << "; " << suma.getY() << "; "  << suma.getZ() << std::endl;


        sredni.R(suma.getX());
        sredni.G(suma.getY());
        sredni.B(suma.getZ());

//        sredni = sredni/25;
//        std::cout << sredni.getRed() << "; " << sredni.getGreen() << "; "  << sredni.getBlue() << std::endl;

        return (sredni);

    }

};