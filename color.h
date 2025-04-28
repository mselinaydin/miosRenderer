//
//  color.h
//

#ifndef color_h
#define color_h

#include "interval.h"
#include "vec3.h"

using color = vec3;

inline double linearToGamma(double linearComponent) {
    if(linearComponent > 0)
        return std::sqrt(linearComponent);
    
    return 0;
}

color getColor(const color& pixelColor) {
    auto r = pixelColor.x;
    auto g = pixelColor.y;
    auto b = pixelColor.z;
    
    // Apply a linear to gamma transform for gamma 2
    r = linearToGamma(r);
    g = linearToGamma(g);
    b = linearToGamma(b);
    
    // Translate the [0, 1] component values to the byte range [0, 255]
    static const interval intensity(0.000, 0.999);
    int rbyte = int(256 * intensity.clamp(r));
    int gbyte = int(256 * intensity.clamp(g));
    int bbyte = int(256 * intensity.clamp(b));

    return color(rbyte, gbyte, bbyte);
}

#endif /* color_h */
