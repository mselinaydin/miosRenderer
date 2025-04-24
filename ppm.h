//
//  ppm.h
//  

#ifndef ppm_hpp
#define ppm_hpp

#include <stdio.h>
#include <fstream>
#include <string>
#include <vector>
#include "vec3.h"

bool writePPM(std::string filename, std::vector<vec3>& data, int width, int height);

#endif /* ppm_hpp */
