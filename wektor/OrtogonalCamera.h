#include "Geometry.h"
#include "AmbientLight.h"
#include "PointLight.h"
using namespace  std;

class OrtogonalCamera {
public:
    Vector positionOrto;
    Vector lookAtOrto;
    Vector upOrto;

public:

    OrtogonalCamera(Vector positionOrto, Vector lookAtOrto, Vector upOrto) : positionOrto(
            positionOrto), lookAtOrto(lookAtOrto), upOrto(upOrto) {}

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

        // Combine specular and diffuse intensities
        Intensity finalIntensity = sIntensity + diffuseIntensity;

        // Apply ambient light
        Intensity ambientColor = ambientLight.getColor();
        float tmp = ambientLight.getIntensity();
        ambientColor *= tmp;
        finalIntensity += ambientColor;

        if (inShadow) finalIntensity *= 0.6; // Adjust this value as needed

        return finalIntensity;
    }
    static Material antyaliasingOrto(int sampling, float antialiasingPixelX, float antialiasingPixelY, float antialiasingPixelSize, Ray raySampling, std::list<Geometry*> objects, Ray rayOrthographic, PointLight pointLight, Vector start, Vector finish, AmbientLight ambientLight){
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
                Ray objectToLight(closestIntersection.LPOINT, pointLight.location);


                if (closestIntersection.type == HIT) {
                    //sprawdzamy malego nibypixela czy jest zacieniony
                    IntersectionResult closestIntersectionShadow;
                    closestIntersectionShadow.type = MISS;
                    closestIntersectionShadow.distance = std::numeric_limits<float>::infinity(); // jak tu jest nieskonczonosc to jakikolwiek hit bedzie mniejszy
                    for (auto obj: objects) {  //jednym z obiektow jhest farplane

                        IntersectionResult intersection = obj->collision(objectToLight, 0.001, objectToLight.getDistance()+0.001);

                        if (intersection.type == HIT && intersection.distance < closestIntersectionShadow.distance) {
//                            std::cout << "siema" << std::endl;
                            closestIntersectionShadow = intersection;
//                            cout<<objectToLight.showCoordinates()<<endl;
                        }
                    }
                    if (closestIntersectionShadow.type == MISS) {   // czyli niezacieniony
                        // tutaj obliczenia jak ten maly pixel wyglada bez cienia,
//                        Intensity colorShadow(0,0,0); //zacienione bedzie czarne
                        Intensity colorNotShadow = calculatePhong(start, closestIntersection, pointLight,
                                                                  false, objectToLight, ambientLight);
                        Material meanColor(colorNotShadow, 0, 0, 0);

                        Colors[iterator] = meanColor;
//                        std::cout << meanColor.color.R() << meanColor.color.G() << meanColor.color.B() << std::endl;


                    } else { //wtedy kiedy okazuje sie ze jest zacieniony punkt
//                        Intensity colorShadow(0,1,1); //zacienione bedzie czarne
//                        std::cout << "siema" << std::endl;
//                        Intensity Red(1,1,1);
// todo: w tego elsa wchodzi zbyt czesto
                        Intensity colorShadow = calculatePhong(start, closestIntersection,
                                                               pointLight, true, objectToLight, ambientLight);
//                        Intensity kupa(0,0,0);
                        Material meanColor(colorShadow, 0, 0, 0);

                        Colors[iterator] = meanColor;
//                        std::cout << meanColor.color.R() << meanColor.color.G() << meanColor.color.B() << std::endl;
                    }
                }

                iterator++;
            }

        }


        Material meanColor1;
        Vector colorsVector(0, 0, 0);
        Vector sum(0, 0, 0);
        for(int s = 0; s<sampling*sampling; ++s){
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

        return (meanColor1);
    }
};