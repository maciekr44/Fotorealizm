//
// Created by Kiu on 28.03.2024.
//

#include "PointLight.h"
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
//
//// Calculate specular component of lighting
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
PointLight::PointLight(Vector location, float constAtten, float linearAtten, float quadAtten) : location(
        location), constAtten(constAtten), linearAtten(linearAtten), quadAtten(quadAtten) {}
