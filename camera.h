//
//  camera.h
//

#ifndef camera_h
#define camera_h

#include "hittable.h"
#include "ppm.h"
#include <vector>

using namespace std;

class camera {
    public:
        double  aspectRatio = 1.0;      // Ratio of image width over height
        int     imageWidth = 100;       // Rendered image width in pixel count
        int     samplesPerPixel = 10;   // Count of random samples per pixel
    
        void render(const hittable& world) {
            initialize();
            
            std::cout << "Image Width: " << imageWidth << " Image Height: " << imageHeight << endl;
            
            vector<vec3> image;
            string outFile = "outFile.ppm";
            
            for(int j = 0; j < imageHeight; j++) {
                for(int i = 0; i < imageWidth; i++) {
                    color pixelColor(0, 0, 0);
                    for(int sample = 0; sample < samplesPerPixel; sample++) {
                        ray r = getRay(i, j);
                        pixelColor += rayColor(r, world);
                    }
                    image.push_back(pixelColor * pixelSamplesScale);
                }
            }
            
            writePPM(outFile, image, imageWidth, imageHeight);
        }
    
    private:
        int     imageHeight;        // Rendered image height
        double  pixelSamplesScale;  // Color scale factor for a sum of pixel samples
        point3  center;             // Camera center
        point3  pixel00Loc;         // Location of pixel 0, 0
        vec3    pixelDeltaU;        // Offset to pixel to the right
        vec3    pixelDeltaV;        // Offset to pixel below
        
        void initialize() {
            imageHeight = int(imageWidth / aspectRatio);
            imageHeight = imageHeight < 1 ? 1 : imageHeight;
            
            pixelSamplesScale = 1.0 / samplesPerPixel;
            
            center = point3(0, 0, 0);
            
            // Determine viewport dimensions
            auto focalLength = 1.0;
            auto viewportHeight = 2.0;
            auto viewportWidth = viewportHeight * (double(imageWidth) / imageHeight);
            
            // Calculate the vectors across the horizontal and down the vertical viewport edges
            auto viewportU = vec3(viewportWidth, 0, 0);
            auto viewportV = vec3(0, -viewportHeight, 0);
            
            // Calculate the horizontal and vertical delta vectors from pixel to pixel.
            pixelDeltaU =  viewportU / imageWidth;  //viewportU / imageWidth;
            pixelDeltaV =  viewportV / imageHeight;  //viewportV / imageHeight;
            
            // Calculate the location of the upper left pixel.
            auto viewportUpperLeft = center - vec3(0, 0, focalLength) - viewportU/2 - viewportV/2;
            pixel00Loc = viewportUpperLeft + (pixelDeltaU + pixelDeltaV) * 0.5;
        }
    
        ray getRay(int i, int j) const {
            // Construct a camera ray originating from the origin and directed at randomly sampled
            // point around the pixel location i, j.
            
            auto offset = sampleSquare();
            auto pixelSample = pixel00Loc
                             + (pixelDeltaU * (i + offset.x))
                             + (pixelDeltaV * (j + offset.y));
            
            auto rayOrigin = center;
            auto rayDirection = pixelSample - rayOrigin;
            
            return ray(rayOrigin, rayDirection);
                    
        }
    
        vec3 sampleSquare() const {
            // Returns the vector to a random point in the [-.5,-.5]-[+.5,+.5] unit square.
            return vec3(randomDouble() - 0.5, randomDouble() - 0.5, 0);
        }
    
        color rayColor(const ray& r, const hittable& world) const {
            hitRecord rec;
            
            if(world.hit(r, interval(0, infinity), rec))
                return (rec.normal + color(1, 1, 1)) * 0.5;
            
            vec3 unitDirection = (r.direction()).normalize();
            auto a = 0.5 * (unitDirection.y + 1.0);
            return color(1.0, 1.0, 1.0) * (1 - a) + color(0.5, 0.7, 1.0) * a;
        }
};


#endif /* camera_h */
