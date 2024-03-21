//
// Created by Kiu on 17.03.2024.
//

//#include "Triangle.h"

#include "Triangle.h"
#include <limits>

using namespace std;

Triangle::Triangle(const Vector &vertex1, const Vector &vertex2, const Vector &vertex3, Intensity color) : Vertex1_(vertex1), Vertex2_(vertex2), Vertex3_(vertex3), Color_(color){

}

//Triangle::Triangle(const Vector &vertex1, const Vector &vertex2, const Vector &vertex3, const Vector &normal1,
//                   const Vector &normal2, const Vector &normal3) {
//
//}

IntersectionResult Triangle::IntersectTriangle(Ray ray, Vector A, Vector B, Vector C) {
    IntersectionResult result;
    result.type = MISS;
    Vector originalA = A;
    Vector originalB = B;
    Vector originalC = C;
    B.sub(A);
    Vector AB = B;
    C.sub(A);
    Vector AC = C;
    Vector normal = AB.cross(AC);
    Vector originalNormal = normal;
    const float EPSILON = std::numeric_limits<float>::epsilon();

    float dot = normal.dotProduct(ray.getDirection());
    if (fabsf(dot) < EPSILON){
        cout << "Ray is parallel to the triangle." << endl;
        return result;
    }
    A.sub(ray.Origin());
    float tmp = normal.dotProduct(A);
    float t = tmp / dot;

    if (t < 0.0f){
        cout << "Intersection point is behind the ray's origin." << endl;
        return result;
    }

    Vector original = ray.getOrigin();
    Vector direction = ray.getDirection();


    direction.mag(t);

    original.add(direction);

    result.LPOINT = original;

    Vector tmp1 = result.LPOINT;
    Vector tmp2 = result.LPOINT;
    Vector tmp3 = result.LPOINT;

    tmp1.sub(originalA);
    Vector AP = tmp1;

    tmp2.sub(originalB);
    Vector BP = tmp2;

    tmp3.sub(originalC);
    Vector CP = tmp3;

    Vector v1 = AB.cross(AP);
    Vector v2 = AC.cross(BP);
    C.sub(originalB);
    Vector v3 = C.cross(CP);

    if (v1.dotProduct(normal) >= 0.0f && v2.dotProduct(normal) >= 0.0f && v3.dotProduct(normal) >= 0.0f){
        cout << "intersection point: " << result.LPOINT.showCoordinates() << endl;
//        result.color = this->Color_;
        result.type = HIT;
        Vector subdywizja = result.LPOINT;
        subdywizja.sub(ray.Origin());
        result.distance = subdywizja.length();
        result.intersectionLPOINTNormal = originalNormal;
        return result;
    }
    cout << "intersection point doesnt exist" << endl;
    return result;
}


