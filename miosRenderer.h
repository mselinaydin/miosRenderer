//
//  miosRenderer.h
//
//  Generic header

#ifndef miosRenderer_h
#define miosRenderer_h

#pragma once

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <memory>

// C++ Std Usings

using std::make_shared;
using std::shared_ptr;

// Constants

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// Utility Functions

inline double degreesToRadians(double degrees) {
    return degrees * pi / 180.0;
}

// Common Headers

#include "utilities.h"
#include "ray.h"
#include "vec3.h"
#include "interval.h"

#endif /* miosRenderer_h */
