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

#endif /* material_h */
