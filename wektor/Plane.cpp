//
// Created by Maciek on 13.03.2024.
//

#include "Plane.h"
using namespace std;

Plane::Plane(Vector normal_vector, Vector point, Intensity color) : Normal_vector_(normal_vector), Point_(point), Color_(color) {}

const Vector &Plane::getNormalVector() const {
    return Normal_vector_;
}

void Plane::setNormalVector(const Vector &normalVector) {
    Normal_vector_ = normalVector;
}

const Vector &Plane::getPoint() const {
    return Point_;
}

void Plane::setPoint(const Vector &point) {
    Point_ = point;
}

string Plane::showCoordinates() const {
    return string("[(") + to_string(getNormalVector().getX()) + string(", ") + to_string(getNormalVector().getY()) + string(", ") + to_string(getNormalVector().getZ()) + string("), (") + to_string(getPoint().getX()) + string(", ") + to_string(getPoint().getY()) + string(", ") + to_string(getPoint().getZ()) + string(")") + string("]");
}

//IntersectionResult Plane::collision(Ray ray, float t_max, float t_min) const {   //todo: ej bo ta funkcja cos nie tego bo nigdy sie nie wydarza hit
//    float range = t_max - t_min;
//    IntersectionResult result;
//    Vector original = ray.getOrigin();
//    Vector normal = getNormalVector();
//    Vector direction = ray.getDirection();
//    Vector point = getPoint();
//    result.type = MISS;
//
//    float ndotD = normal.dotProduct(ray.getDirection());
//    if(ndotD==0) {
//        return result;
//    }
//    float t;
//    original.sub(point);
//    Vector originalAbs = original.abs(original);
//    t = (normal.dotProduct(originalAbs)) / ndotD;
//    if(t>0) {
//        if(range==0.0f || t<range) {
//            result.color = this->Color_;
//
//            if(normal.dotProduct(direction) < 0) {
//                cout << "siema" << endl;
//                result.type = HIT;
//            }
//            else{
//                cout << "cze" << endl;
//                result.type = INSIDE_PRIMITIVE;
//            }
//            direction.mag(t);
//            direction.add(original);
//            result.LPOINT = direction;
//            result.distance = t;
//            result.intersectionLPOINTNormal = normal;
//        }
//    }
//    return result;
//}
//IntersectionResult Plane::collision(Ray ray, float t_min, float t_max) const {
//    IntersectionResult result;
//    result.type = IntersectionType::MISS;
//    const float epsilon = 1e-6f;
//
//    // Calculate the dot product of the ray direction and the plane normal
//    Vector normal = getNormalVector();
//    float denominator = normal.dotProduct(ray.getDirection());
//
//    // Check if the ray is parallel or nearly parallel to the plane
//    if (fabs(denominator) > epsilon) {
//        // Calculate the distance from the ray origin to the plane along the ray direction
//        Vector point = this->getPoint();
//        Vector origin = ray.getOrigin();
//        origin.dotProduct(normal);
//        origin.div(denominator);
//        point.sub(origin);
//        float t = point.length();
//
//        // Check if the intersection point is within the valid range
//        if (t >= t_min && t <= t_max) {
//            result.type = IntersectionType::HIT;
//            result.distance = t;
//            result.LPOINT = ray.pointAtParameter(t);
//            result.intersectionLPOINTNormal = normal;
//            result.color = this->Color_; // Assuming the plane has a material property
//            // Other relevant information...
//        }
//    }
//
//    return result;
//}
IntersectionResult Plane::collision(Ray ray, float t_min, float t_max) const {
    IntersectionResult result;
    result.type = IntersectionType::MISS;
    const float epsilon = 1e-6f;

    // Calculate the dot product of the ray direction and the plane normal
    Vector normal = getNormalVector();
    float denominator = normal.dotProduct(ray.getDirection());

    // Check if the ray is parallel or nearly parallel to the plane
    if (fabs(denominator) > epsilon) {
        // Calculate the distance from the ray origin to the plane along the ray direction
        Vector point = this->getPoint();
        point.sub(ray.getOrigin());
        Vector origin_to_point = point;
        float t = origin_to_point.dotProduct(normal) / denominator;

        // Check if the intersection point is within the valid range
        if (t >= t_min && t <= t_max) {
            result.type = IntersectionType::HIT;
            result.distance = t;
            result.LPOINT = ray.pointAtParameter(t);
            result.intersectionLPOINTNormal = normal;
            result.color = this->Color_; // Assuming the plane has a material property
            // Other relevant information...
        }
    }

    return result;
}