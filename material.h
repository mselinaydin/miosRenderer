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
        metal(const color& _albedo, double _fuzz) : albedo(_albedo), fuzz(_fuzz < 1 ? _fuzz : 1) {}
    
        bool scatter(const ray& rIn, const hitRecord& rec, color& attenuation, ray& scattered) const override {
            vec3 reflected = reflect(rIn.direction(), rec.normal);
            reflected = reflected.normalize() + (fuzz * randomUnitVector());
            scattered = ray(rec.p, reflected);
            attenuation = albedo;
            return (scattered.direction().dot(rec.normal) > 0);
        }
        
    private:
        color albedo;
        double fuzz;
};

class dielectric : public material {
    public:
        dielectric (double _refractionIndex) : refractionIndex(_refractionIndex) {}
        bool scatter(const ray& rIn, const hitRecord& rec, color& attenuation, ray& scattered) const override {
            attenuation = color(1.0, 1.0, 1.0);
            double ri = rec.frontFace ? (1.0 / refractionIndex) : refractionIndex;
            
            vec3 unitDirection = rIn.direction().normalize();
            double cosTheta = std::fmin((-unitDirection).dot(rec.normal), 1.0);
            double sinTheta = std::sqrt(1.0 - cosTheta * cosTheta);
            
            bool cannotRefract = ri * sinTheta > 1.0;
            vec3 direction;
            
            if(cannotRefract || reflectance(cosTheta, ri) > randomDouble())
                direction = reflect(unitDirection, rec.normal);
            else
                direction = refract(unitDirection, rec.normal, ri);
            
            scattered = ray(rec.p, direction);
            return true;
        }
    private:
        // Refractive index in vacuum or air, or the ratio of the material's refractive index over
        // the refractive index of the enclosing media
        double refractionIndex;
    
        static double reflectance(double cosine, double refractionIndex) {
            // Use Schlick's approximation for reflectance.
            auto r0 = (1 - refractionIndex) / (1 + refractionIndex);
            r0 = r0 * r0;
            return r0 + (1-r0)*std::pow((1 - cosine), 5);
        }
};

#endif /* material_h */
