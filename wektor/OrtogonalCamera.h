//#include "Geometry.h"
using namespace  std;

class OrtogonalCamera {
public:
    Vector positionOrto;
    Vector lookAtOrto;
    Vector upOrto;

public:

    OrtogonalCamera(Vector positionOrto, Vector lookAtOrto, Vector upOrto) : positionOrto(
            positionOrto), lookAtOrto(lookAtOrto), upOrto(upOrto) {}

//    static Material antyaliasingOrto(int sampling, float antialiasingPixelX, float antialiasingPixelY, float antialiasingPixelSize, Ray raySampling, std::list<Geometry*> objects, Ray rayOrthographic, PointLight pointLight, Vector cameraPositionOrto){
//        int iterator = 0;
//        IntersectionResult closestIntersection;
//        Material Colors[sampling * sampling];
//        for(int t = 0; t<sampling; ++t){
//            for(int p = 0; p<sampling; ++p){
//                Vector samplingOrigin(0, antialiasingPixelX + (antialiasingPixelSize * t), antialiasingPixelY + (antialiasingPixelSize * p));
//                raySampling.setOrigin(samplingOrigin);
//                Vector samplingDestination(100, antialiasingPixelX + (antialiasingPixelSize * t), antialiasingPixelY + (antialiasingPixelSize * p));
//                raySampling.setDestination(samplingDestination);
//
//                closestIntersection.distance = std::numeric_limits<float>::infinity(); // jak tu jest nieskonczonosc to jakikolwiek hit bedzie mniejszy
//
//                for (auto obj : objects) {  //jednym z obiektow winien byc farplane
//                    IntersectionResult intersection = obj->collision(raySampling, 0, 1000);
//                    if (intersection.type == HIT && intersection.distance < closestIntersection.distance) {
//                        closestIntersection = intersection;
////                        cout<<closestIntersection.LPOINT.showCoordinates()<<endl;
//                    }
//                }
////                 zakomentowany kod to poczatek pracy nad obliczanie phonga
//                Ray objectToLight(closestIntersection.LPOINT, pointLight.location);  //od punktu przeciecia do zrodla swiatla
////                cout<<pointLight.location.showCoordinates()<<endl;
////                std::cout << objectToLight.showCoordinates() << std::endl; //tu jest git
//                //jezeli jest HIT (ray napotkal obiekt) to sprawdzamy czy dany pixel (intersection) jest w cieniu
//                if (closestIntersection.type == HIT){
//                    //sprawdzamy malego nibypixela czy jest zacieniony
//                    IntersectionResult closestIntersectionShadow;
//                    closestIntersectionShadow.type = MISS;
//                    closestIntersectionShadow.distance = std::numeric_limits<float>::infinity(); // jak tu jest nieskonczonosc to jakikolwiek hit bedzie mniejszy
//                    for (auto obj: objects) {  //jednym z obiektow jhest farplane
//                        IntersectionResult intersection = obj->collision(objectToLight, 0, 1000);
//                        if (intersection.type == HIT && intersection.distance < closestIntersectionShadow.distance) {
////                            std::cout << "siema" << std::endl;
//                            closestIntersectionShadow = intersection;
////                            cout<<objectToLight.showCoordinates()<<endl;
//                        }
//                    }
//                    if (closestIntersectionShadow.type == MISS) {   // czyli niezacieniony
//                        // tutaj obliczenia jak ten maly pixel wyglada bez cienia, todo: tj robimy phonga
////                        Intensity colorShadow(0,0,0); //zacienione bedzie czarne
//                        Intensity colorNotShadow = pointLight.calculatePhong(cameraPositionOrto, closestIntersection, pointLight, false, objectToLight);
//                        Intensity colorek(1,1,0);
//                        Material meanColor(colorek,0,0,0);
//                        Colors[iterator] = closestIntersection.material;
//
//
//                    } else { //wtedy kiedy okazuje sie ze jest zacieniony punkt todo: tutaj wzor od Michala most likely
////                        Intensity colorShadow(0,1,1); //zacienione bedzie czarne
////                        std::cout << "siema" << std::endl;
////                        Intensity Red(1,1,1);
//                        Intensity colorShadow = pointLight.calculatePhong(cameraPositionOrto, closestIntersection, pointLight, true, objectToLight);
//                        Intensity colorek(1,0,1);
//                        Material meanColor(colorek,0,0,0);
//
//                        Colors[iterator] = meanColor;
//
//                    }
//                }
//            }
////            Colors[iterator] = closestIntersection.material;    // to zakomentowac jak bedzie phong
//            iterator++;
//
//        }
//        Material meanColor;
//        Vector colorsVector(0, 0, 0);
//        Vector sum(0, 0, 0);
//        for(int s = 0; s<sampling*sampling; ++s){
//            meanColor = Colors[s];
//            colorsVector.setX(meanColor.color.getRed());
//            colorsVector.setY(meanColor.color.getGreen());
//            colorsVector.setZ(meanColor.color.getBlue());
//
//            sum.add(colorsVector);
//
//        }
//        sum.div(sampling * sampling);
//
//        meanColor.color.R(sum.getX());
//        meanColor.color.G(sum.getY());
//        meanColor.color.B(sum.getZ());
//
//        return (meanColor);
//    }

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