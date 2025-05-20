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
    vec3 cross(const vec3& v) const { return vec3(y * v.z - z * v.y,
                                                  z * v.x - x * v.z,
                                                  x * v.y - y * v.x); }
    double lengthSquared() const { return x * x + y * y + z * z; }
    double length() const { return std::sqrt(lengthSquared()); }
    bool nearZero() const {
        // Return true if the vector is close to zero in all dimensions.
        auto s = 1e-8;
        return (std::fabs(x < s)) && (std::fabs(y < s)) && (std::fabs(z < s));
    }
    static vec3 random() {
        return vec3(randomDouble(), randomDouble(), randomDouble());
    }
    static vec3 random(double min, double max) {
        return vec3(randomDouble(min, max), randomDouble(min, max), randomDouble(min, max));
    }
};

using point3 = vec3;

using color = vec3;

// Vector utility functions

inline vec3 operator*(const vec3& u, const vec3& v) {
    return vec3(u.x * v.x, u.y * v.y, u.z * v.z);
}

inline vec3 operator*(double t, const vec3& v) {
    return vec3(t * v.x, t * v.y, t * v.z);
}


inline vec3 randomUnitVector() {
    while(true) {
        auto p = vec3::random(-1, 1);
        auto lensq = p.lengthSquared();
        if(1e-160 < lensq && lensq <= 1)
            return p / sqrt(lensq);
    }
}

inline vec3 randomInUnitDisk() {
    while(true) {
        auto p = vec3(randomDouble(-1, 1), randomDouble(-1, 1), 0);
        if(p.lengthSquared() < 1)
            return p;
    }
}

inline vec3 randomOnHemisphere(const vec3& normal) {
    vec3 onUnitSphere = randomUnitVector();
    if(onUnitSphere.dot(normal) > 0.0) // In the same hemisphere as the normal
        return onUnitSphere;
    else
        return -onUnitSphere;
}

inline vec3 reflect(const vec3& v, const vec3& n) {
    return v - v.dot(n) * n * 2;
}

inline vec3 refract(const vec3& uv, const vec3& n, double etaiOverEtat) {
    auto cosTheta = std::fmin((-uv).dot(n), 1.0);
    vec3 rOutPerp = etaiOverEtat * (uv + cosTheta * n);
    vec3 rOutParallel = -std::sqrt(std::fabs(1.0 - rOutPerp.lengthSquared())) * n;
    return rOutPerp + rOutParallel;
}

#endif /* vec3_h */
