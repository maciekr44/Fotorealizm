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

    static Material
    antyaliasingPersp(int sampling, float antialiasingPixelX, float antialiasingPixelY, float antialiasingPixelSize,
                      Ray raySampling, list<Geometry *> objects, Ray rayOrthographic, PointLight pointLight,
                      Vector start,
                      Vector intersection, AmbientLight ambientLight) {
        int iterator = 0;
        IntersectionResult closestIntersection;
        Material Colors[sampling * sampling];

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
                Colors[iterator] = closestIntersection.material;
                iterator++;


            }
        }
        Material meanColor;
        Vector colorsVector(0, 0, 0);
        Vector sum(0, 0, 0);
        for (int s = 0; s < sampling * sampling; ++s) {
            meanColor = Colors[s];
            colorsVector.setX(meanColor.color.getRed());
            colorsVector.setY(meanColor.color.getGreen());
            colorsVector.setZ(meanColor.color.getBlue());

            sum.add(colorsVector);
        }

        sum.div(sampling * sampling);

        meanColor.color.R(sum.getX());
        meanColor.color.G(sum.getY());
        meanColor.color.B(sum.getZ());

//        Vector jeden = meanColor.color.calculateIntensity(pointLight, intersection);
        Vector dwa = calculateIntensity2(pointLight, intersection);


        Intensity newColor(meanColor.color.R() * dwa.getX(), meanColor.color.G() * dwa.getY(),
                           meanColor.color.B() * dwa.getZ());
//            cout<<pointLight.location.showCoordinates()<<endl;
        Ray objectToLight(closestIntersection.LPOINT, pointLight.location);
        Intensity final = calculatePhong(start, closestIntersection, pointLight, true, objectToLight, ambientLight);
        Material newMaterial(final, 0, 0, 0);
        return (newMaterial);


    }
};
