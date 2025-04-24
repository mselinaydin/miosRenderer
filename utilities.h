//
//  utilities.h
//  

#ifndef utilities_h
#define utilities_h

inline double randomDouble() {
    // Returns a random real in [0, 1)
    return std::rand() / (RAND_MAX + 1.0);
}

inline double randomDouble(double min, double max) {
    // Returns a random real in [min, max)
    return min + (max - min) * randomDouble();
}

#endif /* utilities_h */
