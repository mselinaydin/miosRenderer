//
//  ppm.cpp
//  

#include "ppm.h"
using namespace std;

bool writePPM(string filename, vector<vec3>& data, int width, int height) {
    if(width <= 0 || height <= 0)
        return false;
    
    ofstream image(filename);
    image << "P3\n" << width << " " << height << "\n255\n";
    
    for(int i = 0; i < data.size(); i++) {
        image   << data[i].x << " "
                << data[i].y << " "
                << data[i].z << endl;
    }
    
    image.close();
    return true;
}
