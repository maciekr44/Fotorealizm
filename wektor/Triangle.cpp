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



