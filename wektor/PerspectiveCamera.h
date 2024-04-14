#include "Geometry.h"
#include "PointLight.h"
#include "AmbientLight.h"
#include <list>
using namespace std;

class PerspectiveCamera {
private:
    Vector position;
    Vector lookAt;
    Vector up;
    float fov;

public:
    PerspectiveCamera(Vector position, Vector lookAt, Vector up, float fov) : position(position), lookAt(lookAt), up(up), fov(fov){}

    static Vector calculateIntensity2(PointLight pointLight, Vector Op) {
        Ray distance(pointLight.location, Op);
        float I = 1.0 / (pointLight.constAtten + (pointLight.linearAtten * abs(distance.getDistance())));
        Vector In(I, I, I);
//    cout<<I.showCoordinates()<<endl;
        return In;
    }



//    static Intensity calculatePhong(Vector cameraPosition, IntersectionResult result, PointLight light, bool inShadow, Ray raySampling) {
//        Vector I = raySampling.getDirection();
//        I.normalize();
//        Vector N = result.intersectionLPOINTNormal;
//        N.normalize();
//
//        // Calculate reflection vector
//        Vector R = N;
//        float TMPR = R.dotProduct(I);
//        R.mag(TMPR);
//        R.mag(2);
//        R.sub(I);
//        R.normalize();
//
//        // Calculate specular component
//        float ss = std::max(0.0f, raySampling.getDirection().dotProduct(R));
//        float specular = (ss > 0) ? std::pow(ss, result.material.shineness) * result.material.specular : 0;
//        Intensity sIntensity = light.color;
//        sIntensity *= specular;
//
//        // Calculate diffuse component
//        float cosinus = std::max(0.0f, raySampling.getDirection().dotProduct(N));
//        Intensity diffuseIntensity = result.material.color;
//        diffuseIntensity *=  cosinus;
//
//        // Combine specular and diffuse intensities
//        Intensity finalIntensity = sIntensity + diffuseIntensity;
//
//        return finalIntensity;
//    }
//
//    // Calculate the right vector based on the up vector and the direction from camera position to lookAt
//    Vector right() const {
//        Vector direction = lookAt;
//        direction.sub(position);
//        Vector right = direction.cross(up);
//        return right;
//    }
    static Intensity calculatePhong(Vector cameraPosition, IntersectionResult result, PointLight light, bool inShadow, Ray raySampling, AmbientLight ambientLight) {
        Vector I = raySampling.getDirection();
        I.normalize();
        Vector N = result.intersectionLPOINTNormal;
        N.normalize();

        // Calculate reflection vector
        Vector R = N;
        float TMPR = R.dotProduct(I);
        R.mag(TMPR);
        R.mag(2);
        R.sub(I);
        R.normalize();

        // Calculate distance from light to intersection point
        Vector lightDirection = light.location;
        lightDirection.sub(result.LPOINT);
        Vector distanceToLight = lightDirection;
        distanceToLight.sub(result.LPOINT);
        float distanceToLightFloat = distanceToLight.length();
//        distanceToLightFloat.normalize();

        // Calculate attenuation
        float attenuation = 1.0f / (light.constAtten + light.linearAtten * distanceToLightFloat);

        // Calculate specular component
        float ss = std::max(0.0f, raySampling.getDirection().dotProduct(R));
        float specular = (ss > 0) ? std::pow(ss, result.material.shineness) * result.material.specular : 0;
        Intensity sIntensity = light.color; // Apply attenuation to specular intensity
        sIntensity *= attenuation;
        sIntensity *= specular;

        // Calculate diffuse component
        float cosinus = std::max(0.0f, raySampling.getDirection().dotProduct(N));
        Intensity diffuseIntensity = result.material.color; // Apply attenuation to diffuse intensity
        diffuseIntensity *= cosinus;
        diffuseIntensity *= attenuation;

//        // Combine specular and diffuse intensities-----------------------------
//        Intensity finalIntensity = sIntensity + diffuseIntensity;
//
//        Intensity ambientColor = ambientLight.getColor();
//        finalIntensity = finalIntensity * ambientColor;--------------------------

//        if(result.type == HIT){
//            if(finalIntensity.R() == 0) finalIntensity.R(0.02);
//            if(finalIntensity.R() == 0) finalIntensity.G(0.02);
//            if(finalIntensity.R() == 0) finalIntensity.B(0.02);
//
//            float newR = finalIntensity.R() * ambientLight.getIntensity();
//            float newG = finalIntensity.G() * ambientLight.getIntensity();
//            float newB = finalIntensity.B() * ambientLight.getIntensity();
//
//            finalIntensity.R(newR);
//            finalIntensity.G(newG);
//            finalIntensity.B(newB);
//        }


        // Combine specular and diffuse intensities
        Intensity finalIntensity = sIntensity + diffuseIntensity;

        // Apply ambient light
        Intensity ambientColor = ambientLight.getColor();
        float tmp = ambientLight.getIntensity();
        ambientColor*=tmp;
        finalIntensity += ambientColor;

        return finalIntensity;

//        finalIntensity *= ambientLight.getIntensity();-------------------------

        return finalIntensity;
    }

    static Material antyaliasingPersp(int sampling, float antialiasingPixelX, float antialiasingPixelY, float antialiasingPixelSize,
                      Ray raySampling, list<Geometry *> objects, Ray rayOrthographic, PointLight pointLight,
                      Vector start,
                      Vector intersection, AmbientLight ambientLight) {
        int iterator = 0;
        IntersectionResult closestIntersection;
        Material Colors[sampling * sampling];
        Vector cameraPositionPersp = rayOrthographic.getOrigin();

        for (int t = 0; t < sampling; ++t) {
            for (int p = 0; p < sampling; ++p) {

                Vector samplingDestination(0, antialiasingPixelX + (antialiasingPixelSize * t),
                                           antialiasingPixelY + (antialiasingPixelSize * p));
                raySampling.setDestination(samplingDestination);
                // Check for intersections with the sphere

                closestIntersection.distance = std::numeric_limits<float>::infinity(); // jak tu jest nieskonczonosc to jakikolwiek hit bedzie mniejszy

                for (auto obj: objects) {  //jednym z obiektow winien byc farplane
                    IntersectionResult intersection = obj->collision(raySampling, 0, 1000);
                    if (intersection.type == HIT && intersection.distance < closestIntersection.distance) {
                        closestIntersection = intersection;
                    }
                }
//                Colors[iterator] = closestIntersection.material;
//                iterator++;

                //phong, sprawdzanie czy jestesmy w cieniu
                Ray objectToLight(closestIntersection.LPOINT,
                                  pointLight.location);  //od punktu przeciecia do zrodla swiatla
//                cout<<pointLight.location.showCoordinates()<<endl;
//                std::cout << objectToLight.showCoordinates() << std::endl; //tu jest git
                //jezeli jest HIT (ray napotkal obiekt) to sprawdzamy czy dany pixel (intersection) jest w cieniu
                if (closestIntersection.type == HIT) {
                    //sprawdzamy malego nibypixela czy jest zacieniony
                    IntersectionResult closestIntersectionShadow;
                    closestIntersectionShadow.type = MISS;
                    closestIntersectionShadow.distance = std::numeric_limits<float>::infinity(); // jak tu jest nieskonczonosc to jakikolwiek hit bedzie mniejszy
                    for (auto obj: objects) {  //jednym z obiektow jhest farplane
                        IntersectionResult intersection = obj->collision(objectToLight, 0.001, 1000);
                        if (intersection.type == HIT && intersection.distance < closestIntersectionShadow.distance) {
//                            std::cout << "siema" << std::endl;
                            closestIntersectionShadow = intersection;
//                            cout<<objectToLight.showCoordinates()<<endl;
                        }
                    }
                    if (closestIntersectionShadow.type == MISS) {   // czyli niezacieniony
                        // tutaj obliczenia jak ten maly pixel wyglada bez cienia,
//                        Intensity colorShadow(0,0,0); //zacienione bedzie czarne
                        Intensity colorNotShadow = calculatePhong(cameraPositionPersp, closestIntersection, pointLight,
                                                                  false, objectToLight, ambientLight);
                        Material meanColor(colorNotShadow, 0, 0, 0);

                        Colors[iterator] = meanColor;
//                        std::cout << meanColor.color.R() << meanColor.color.G() << meanColor.color.B() << std::endl;


                    } else { //wtedy kiedy okazuje sie ze jest zacieniony punkt
//                        Intensity colorShadow(0,1,1); //zacienione bedzie czarne
//                        std::cout << "siema" << std::endl;
//                        Intensity Red(1,1,1);
                        Intensity colorShadow = calculatePhong(cameraPositionPersp, closestIntersection,
                                                               pointLight, true, objectToLight, ambientLight);
                        Intensity kupa(0,0,0);
                        Material meanColor(kupa, 0, 0, 0);

                        Colors[iterator] = meanColor;
//                        std::cout << meanColor.color.R() << meanColor.color.G() << meanColor.color.B() << std::endl;


                    }
                }
//                std::cout << to_string(iterator) << std::endl;
//                std::cout << Colors[iterator].color.R() << Colors[iterator].color.G() << Colors[iterator].color.B() << std::endl; // tu sa dobrze kolorki
                iterator++;
            }

        }

        Material meanColor1;
        Vector colorsVector(0, 0, 0);
        Vector sum(0, 0, 0);
        for (int s = 0; s < sampling * sampling; ++s) {
//            std::cout << Colors[s].color.R() << Colors[s].color.G() << Colors[s].color.B() << std::endl;    // tu juz nie es

            meanColor1 = Colors[s];
            colorsVector.setX(meanColor1.color.getRed());
            colorsVector.setY(meanColor1.color.getGreen());
            colorsVector.setZ(meanColor1.color.getBlue());

            sum.add(colorsVector);
        }

        sum.div(sampling * sampling);

        meanColor1.color.R(sum.getX());
        meanColor1.color.G(sum.getY());
        meanColor1.color.B(sum.getZ());

//        Vector jeden = meanColor.color.calculateIntensity(pointLight, intersection);
//        Vector dwa = calculateIntensity2(pointLight, intersection);


//        Intensity newColor(meanColor.color.R() * dwa.getX(), meanColor.color.G() * dwa.getY(),
//                           meanColor.color.B() * dwa.getZ());
//            cout<<pointLight.location.showCoordinates()<<endl;
//        Ray objectToLight(closestIntersection.LPOINT, pointLight.location);
//        Intensity final = calculatePhong(start, closestIntersection, pointLight, true, objectToLight, ambientLight);
//        Material newMaterial(final, 0, 0, 0);
        return (meanColor1);


    }
};
