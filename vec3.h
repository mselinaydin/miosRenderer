//
//  vec3.h
//  

#ifndef vec3_h
#define vec3_h

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
};

using point3 = vec3;

using color = vec3;

#endif /* vec3_h */
