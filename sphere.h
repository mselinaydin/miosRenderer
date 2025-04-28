//
//  sphere.h
//  

#ifndef sphere_h
#define sphere_h

#include "hittable.h"

class sphere : public hittable {
    public:
    sphere(const point3& _center, double _radius, shared_ptr<material> _mat) : center(_center), radius(std::fmax(0, _radius)), mat(_mat) {}
    bool hit(const ray& r, interval rayT, hitRecord& rec) const override {
        vec3 oc = center - r.origin();
        auto a = r.direction().lengthSquared();
        auto h = r.direction().dot(oc);
        auto c = oc.lengthSquared() - radius * radius;
        
        auto discriminant = h * h - a * c;
        if(discriminant < 0)
            return false;
        
        auto sqrtd = std::sqrt(discriminant);
        
        // Find the nearest root that lies in the acceptable range
        auto root = (h - sqrtd) / a;
        if(!rayT.surrounds(root)) {
            root = (h + sqrtd) / a;
            if(!rayT.surrounds(root))
                return false;
        }
        
        rec.t = root;
        rec.p = r.at(rec.t);
        vec3 outwardNormal = (rec.p - center) / radius;
        rec.setFaceNormal(r, outwardNormal);
        rec.mat = mat;
        
        return true;
    }
    private:
        point3 center;
        double radius;
        shared_ptr<material> mat;
};

#endif /* sphere_h */
