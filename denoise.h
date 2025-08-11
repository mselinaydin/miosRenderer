//
//  denoise.h
//  
//
//  Created by Melike Selin Aydin
//

#ifndef denoise_h
#define denoise_h

#include <OpenImageDenoise/oidn.hpp>
#include <vector>
#include <algorithm>
#include "vec3.h"

using namespace std;

void denoiseImage(vector<vec3>& image, int width, int height) {
    // Create oidn device
    oidn::DeviceRef device = oidn::newDevice();
    device.commit();
    
    vector<float> colorBuffer(width * height * 3);
    for (size_t i = 0; i < image.size(); ++i)
    {
        colorBuffer[i * 3 + 0] = static_cast<float>(image[i].x) / 255.0f; // R
        colorBuffer[i * 3 + 1] = static_cast<float>(image[i].y) / 255.0f; // G
        colorBuffer[i * 3 + 2] = static_cast<float>(image[i].z) / 255.0f; // B
    }
    
    // Output buffer for denoised image
    std::vector<float> outputBuffer(width * height * 3);
    
    // Create filter
    oidn::FilterRef filter = device.newFilter("RT"); // RT = ray tracing
    filter.setImage("color",  colorBuffer.data(), oidn::Format::Float3, width, height);
    filter.setImage("output", outputBuffer.data(), oidn::Format::Float3, width, height);
    filter.set("hdr", false); // true for HDR images, false for LDR
    filter.commit();

    // Execute filter
    filter.execute();
    
    // Check for errors
    const char* errorMessage;
    if (device.getError(errorMessage) != oidn::Error::None)
    {
        std::cerr << "OIDN error: " << errorMessage << std::endl;
    }

    // Copy back to image
    for (size_t i = 0; i < image.size(); ++i)
    {
        image[i].x = static_cast<int>(outputBuffer[i * 3 + 0] * 255);
        image[i].y = static_cast<int>(outputBuffer[i * 3 + 1] * 255);
        image[i].z = static_cast<int>(outputBuffer[i * 3 + 2] * 255);
    }
}

#endif /* denoise_h */
