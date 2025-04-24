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
        image   << static_cast<int>(data[i].x * 255) << " "
                << static_cast<int>(data[i].y * 255) << " "
                << static_cast<int>(data[i].z * 255) << endl;
    }
    
    image.close();
    return true;
}
