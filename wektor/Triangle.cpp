#include <limits>
#include "Triangle.h"

using namespace std;

Triangle::Triangle(const Vector &vertex1, const Vector &vertex2, const Vector &vertex3, Material material) : Vertex1_(vertex1), Vertex2_(vertex2), Vertex3_(vertex3), Material_(material){

}
IntersectionResult Triangle::collision(Ray ray, float t_min, float t_max) const{
        Vector A = this->Vertex1_;
        Vector B = this->Vertex2_;
        Vector C = this->Vertex3_;
        IntersectionResult result;
        result.type = MISS;
        Vector originalA = A;
        Vector originalB = B;
        Vector originalC = C;
        B.sub(A);
        Vector AB = B;
        C.sub(A);
        Vector AC = C;
//        Vector normal = AB.cross(AC);
        originalC.sub(originalB);
        Vector CB = originalC;
//        Vector originalNormal = normal;
        const float EPSILON = numeric_limits<float>::epsilon();



    Vector normal = ray.getDirection().cross(AC);

    float dotProduct = AB.dotProduct(normal);
//    const float EPSILON = std::numeric_limits<float>::epsilon();
    if (fabsf(dotProduct) < EPSILON) {  //FLT_Epsilon - najmniejsza mozliwa reprezentacja float
        return result;
    }

    Vector origin = ray.getOrigin();
    origin.sub(originalA);
    origin.div(dotProduct);
    float t1 = normal.dotProduct(origin);

    if (t1 < 0.0f) { // tu patrzymy czy trójkąt jest ZA poczatkiem promienia
        return result;
    }
    ray.getDirection().mag(t1);
    Vector originTMP = ray.getOrigin();
    originTMP.add(ray.getDirection());
    Vector collisionPoint =  originTMP;

    Vector originTMP2 = ray.getOrigin();
    originTMP2.sub(originalA);
    Vector s = originTMP2;
    Vector q = s.cross(AB);

    float v = ray.getDirection().dotProduct(q) / dotProduct;

    if (v < 0.0f || t1 + v > 1.0f) {
        return result;
    }

    result.type = HIT;
    result.LPOINT = collisionPoint;
    result.material = this->Material_;
    result.intersectionLPOINTNormal = normal;
    result.distance = collisionPoint.length();
    return result;
}

//
//
//IntersectionResult Triangle::collision(Ray ray, float t_min, float t_max) const {
//    IntersectionResult result;
//    const float EPSILON = std::numeric_limits<float>::epsilon();
//    // Compute the normal of the triangle
//    Vector AB = Vertex2_;
//    AB.sub( Vertex1_);
//    Vector AC = Vertex3_;
//    AC.sub( Vertex1_);
//    Vector tmpAB = AB;
//    tmpAB.cross(AC).normalize();
//    Vector normal = tmpAB;
//
//    // Check for ray-triangle parallelism
//    float dotProduct = ray.getDirection().dotProduct(normal);
//    if (fabsf(dotProduct) < EPSILON) {
//        return result; // Ray is parallel to triangle
//    }
//
//    // Calculate intersection point with the plane containing the triangle
//    Vector tmpRayOrigin = ray.getOrigin();
//    Vector tmpVertex1 = Vertex1_;
//    tmpVertex1.sub(tmpRayOrigin);
////    float aa = tmpVertex1.dotProduct(normal);
////    float bb = aa/dotProduct;
//    float t = tmpVertex1.dotProduct(normal) / dotProduct;
//    if (t < 0.0f) {
//        return result; // Intersection point is behind the ray origin
//    }
//    Vector intersectionPoint = ray.pointAtParameter(t);
//
//    // Check if intersection point lies within the triangle
//    Vector AP = intersectionPoint;
//    AP.sub( Vertex1_);
//    float dotACB = AC.dotProduct(normal);
//    float dotABAB = AB.dotProduct(AB);
//    float dotABAP = AB.dotProduct(AP);
//    float dotACAC = AC.dotProduct(AC);
//    float dotACAP = AC.dotProduct(AP);
//    float denominator = dotABAB * dotACAC - dotABAP * dotABAP;
//    float u = (dotACAC * dotABAP - dotABAB * dotACAP) / denominator;
//    float v = (dotABAB * dotACAP - dotABAP * dotACB) / denominator;
//    if (u >= 0.0f && v >= 0.0f && u + v <= 1.0f) {
//        // Intersection point lies within the triangle
//        result.type = HIT;
//        result.LPOINT = intersectionPoint;
//        result.material = this->Material_;
//        result.intersectionLPOINTNormal = normal;
//        result.distance = t;
//    }
//
//    return result;
//}