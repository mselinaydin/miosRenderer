//
//  vec3.h
//  

#ifndef vec3_h
#define vec3_h

#include "utilities.h"

struct vec3 {
    double x, y, z;
    
    vec3() { x = 0; y = 0; z = 0; };
    vec3(double _x, double _y, double _z) {x = _x; y = _y; z = _z;};
    
    vec3 operator-() const { return vec3(-x, -y, -z); }
    
    vec3 operator+(const vec3& v) const { return {x + v.x, y + v.y, z + v.z}; }
    vec3 operator-(const vec3& v) const { return {x - v.x, y - v.y, z - v.z}; }
    vec3 operator*(double s) const { return {x * s, y * s, z * s}; }
    vec3 operator*(int s) const { return {x * double(s), y * double(s), z * double(s)}; }
    vec3 operator/(int s) const { return {x / s, y / s, z /s}; }
    vec3 operator/(double s) const { return {x / s, y / s, z /s}; }
    vec3 operator+=(const vec3& v) {
        x += v.x;
        y += v.y;
        z += v.z;
        return *this;
    }
    
    vec3 normalize() const { double len = std::sqrt(x*x + y*y + z*z); return {x/len, y/len, z/len}; }
    double dot(const vec3& v) const { return x * v.x + y * v.y + z * v.z; }
    double lengthSquared() const { return x * x + y * y + z * z; }
    static vec3 random() {
        return vec3(randomDouble(), randomDouble(), randomDouble());
    }
    static vec3 random(double min, double max) {
        return vec3(randomDouble(min, max), randomDouble(min, max), randomDouble(min, max));
    }
};

using point3 = vec3;

using color = vec3;

inline vec3 randomUnitVector() {
    while(true) {
        auto p = vec3::random(-1, 1);
        auto lensq = p.lengthSquared();
        if(1e-160 < lensq && lensq <= 1)
            return p / sqrt(lensq);
    }
}

inline vec3 randomOnHemisphere(const vec3& normal) {
    vec3 onUnitSphere = randomUnitVector();
    if(onUnitSphere.dot(normal) > 0.0) // In the same hemisphere as the normal
        return onUnitSphere;
    else
        return -onUnitSphere;
}

#endif /* vec3_h */
