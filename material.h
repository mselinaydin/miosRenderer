//
//  material.h
//

#ifndef material_h
#define material_h

#include "hittable.h"

class material {
    public:
        virtual ~material() = default;
    
    virtual bool scatter(const ray& rIn, const hitRecord& rec, color& attenuation, ray& scattered) const { return false; }
};

class lambertian : public material {
    public:
        lambertian(const color& _albedo) : albedo(_albedo) {}
    
        bool scatter(const ray& rIn, const hitRecord& rec, color& attenuation, ray& scattered) const override {
            auto scatterDirection = rec.normal + randomUnitVector();
            
            // Catch degenerate scatter direction
            if(scatterDirection.nearZero())
                scatterDirection = rec.normal;
            
            scattered = ray(rec.p, scatterDirection);
            attenuation = albedo;
            return true;
        }
    private:
        color albedo;
};

class metal : public material {
    public:
        metal(const color& _albedo) : albedo(_albedo) {}
    
        bool scatter(const ray& rIn, const hitRecord& rec, color& attenuation, ray& scattered) const override {
            vec3 reflected = reflect(rIn.direction(), rec.normal);
            scattered = ray(rec.p, reflected);
            attenuation = albedo;
            return true;
        }
        
    private:
        color albedo;
};

#endif /* material_h */
