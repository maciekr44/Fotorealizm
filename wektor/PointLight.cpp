//
// Created by Kiu on 28.03.2024.
//

#include "PointLight.h"
using namespace std;

//
//// Calculate diffuse component of lighting
//Intensity PointLight::getDiffuse(Vector cameraPosition, IntersectionResult result) {
//    Intensity color;
//    location.sub(result.LPOINT);
//    Vector lightDir = location;
//    float distance = lightDir.length();
//    lightDir.normalize();
//    Vector normal = result.intersectionLPOINTNormal;
//    float cosTheta = normal.dotProduct(lightDir);
//    if (cosTheta < 0) return Intensity(); // Light is behind the surface
//    color *= (cosTheta / (constAtten + linearAtten * distance + quadAtten * distance * distance));
//    return color;
//}
////
////// Calculate specular component of lighting
//Intensity PointLight::getSpecular(Vector cameraPosition, IntersectionResult result) {
//    float shininess;
//    Intensity color;
//    location.sub(result.LPOINT);
//    Vector lightDir = location;
//    float distance = lightDir.length();
//    lightDir.normalize();
//    Vector normal = result.intersectionLPOINTNormal;
//    cameraPosition.sub(result.LPOINT);
//    Vector viewDir = cameraPosition;
//    viewDir.normalize();
//
//    Vector normalTMP = normal;
//    normal.dotProduct(lightDir);
//    normal.mag(2.0f);
//    normalTMP.cross(normal);
//    Vector reflectDir = normalTMP.divVector(lightDir);
//    float cosAlpha = viewDir.dotProduct(reflectDir);
//    if (cosAlpha < 0) return Intensity(); // Light reflection is in opposite direction of view
//    color *= (pow(cosAlpha, shininess) / (constAtten + linearAtten * distance + quadAtten * distance * distance));
//    return color;
//}
//
//// Check if the point light is in shadow for a given intersection point and object
//int PointLight::isInShadow(IntersectionResult iInfo, Geometry* object) {
//    location.sub(iInfo.LPOINT);
//    Vector lightDir = location;
//    float distance = lightDir.length();
//    lightDir.normalize();
//    Ray shadowRay(iInfo.LPOINT, lightDir);
//    IntersectionResult shadowResult = object->collision(shadowRay, 0.001f, distance);
//    return (shadowResult.type == IntersectionType::HIT) ? 1 : 0;
//}

PointLight::PointLight(const Vector& location, float constAtten, float linearAtten, float quadAtten, Intensity color) {

}




Intensity PointLight::calculatePhong(Vector cameraPosition, IntersectionResult result, PointLight light, bool inShadow) {
    // Compute ambient component (usually a fraction of the object's color)
    Intensity ambientColor = result.material.color;

    // calculate distance:
    Ray distanceRay(result.LPOINT, light.location);
    float distance = distanceRay.getDistance();
//    cout << distance << endl;


    // Calculate attenuation
    float attenuation = 1.0f / (light.constAtten + light.linearAtten * distance + light.quadAtten * distance * distance);
    // Apply attenuation to the actual color of the light
    Intensity intensity = light.color;
//    cout << intensity << endl;
    intensity *= attenuation;
//    cout << intensity << endl;

    // Compute diffuse component
    Vector lightDirectionTMP = light.location;
    lightDirectionTMP.sub(result.LPOINT);
    Vector lightDirection = lightDirectionTMP;
    lightDirection.normalize();
    float diffuseFactor = std::max(0.0f, result.intersectionLPOINTNormal.dotProduct(lightDirection));
    Intensity diffuseColor = result.material.color;
    diffuseColor = diffuseColor*intensity;
    diffuseColor*=diffuseFactor;

    // Compute reflection vector and specular component
    float reflection = 2 * result.intersectionLPOINTNormal.dotProduct(lightDirection);
    Vector reflectionVector = result.intersectionLPOINTNormal;
    reflectionVector.mag(reflection);
    reflectionVector.sub(lightDirection);

    reflectionVector.normalize();
    Vector viewDirection = cameraPosition;
    viewDirection.sub(result.LPOINT);
    viewDirection.normalize();
    float specularFactor = std::pow(std::max(0.0f, reflectionVector.dotProduct(viewDirection)), result.material.shineness);
    Intensity specularColor = intensity * result.material.color;
    specularColor *= specularFactor;

    // Check for shadow and adjust components if necessary
    if (inShadow) {
        diffuseColor = Intensity(); // Set diffuse color to black or attenuate it
        specularColor = Intensity(); // Set specular color to black or attenuate it
    }

    // Combine components to get final pixel color
    return ambientColor + diffuseColor + specularColor;
}

Vector PointLight::calculateIntensity(PointLight pointLight, Vector Op) {
    Ray distance(pointLight.location, Op);
    float I = 1.0 / (pointLight.constAtten + (pointLight.linearAtten * abs(distance.getDistance())));
    Vector In(I, I, I);
//    cout<<I.showCoordinates()<<endl;
    return In;
}

Vector PointLight::isInShadow(PointLight pointLight, Vector Op) {
    Vector In(1, 0, 1);
//    cout<<I.showCoordinates()<<endl;
    return In;
}
