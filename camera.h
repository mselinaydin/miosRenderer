//
//  camera.h
//

#ifndef camera_h
#define camera_h

#include "hittable.h"
#include "ppm.h"
#include "color.h"
#include "material.h"
#include <vector>
#include "denoise.h"

using namespace std;

class camera {
    public:
        double  aspectRatio     = 1.0;  // Ratio of image width over height
        int     imageWidth      = 100;  // Rendered image width in pixel count
        int     samplesPerPixel = 10;   // Count of random samples per pixel
        int     maxDepth        = 10;   // Maximum number of ray bounces into scene
    
        double  vfov            = 90;               // Vertical view angle (field of view)
        point3  lookFrom        = point3(0, 0, 0);  // Point camera is looking from
        point3  lookAt          = point3(0, 0, -1); // Point camera is looking at
        vec3    vup             = vec3(0, 1, 0);    // Camera-relative "up" direction
    
        double  defocusAngle    = 0;     // Variation angle of rays through each pixel
        double  focusDist       = 10;    // Distance from camera lookFrom point to plane of perfect focus
    
        bool    doDenoise       = false; // Option to turn on Intel OIDN denoising
    
        void render(const hittable& world) {
            initialize();
            
            std::cout << "Image Width: " << imageWidth << " Image Height: " << imageHeight << endl;
            
            vector<vec3> image;
            string outFile = "outputImage.ppm";
            
            for(int j = 0; j < imageHeight; j++) {
                for(int i = 0; i < imageWidth; i++) {
                    color pixelColor(0, 0, 0);
                    for(int sample = 0; sample < samplesPerPixel; sample++) {
                        ray r = getRay(i, j);
                        pixelColor += rayColor(r, maxDepth, world);
                    }
                    
                    color finalColor = getColor(pixelColor * pixelSamplesScale);
                    
                    image.push_back(finalColor);
                }
            }
            
            // Write rendered image to file
            writePPM(outFile, image, imageWidth, imageHeight);
            
            // Denoise with oidn if turned on
            if(doDenoise) {
                // Denoise image using oidn
                denoiseImage(image, imageWidth, imageHeight);
                
                // Write denoised image to file
                string outFile2 = "denoisedOutputImage.ppm";
                writePPM(outFile2, image, imageWidth, imageHeight);
            }
        }
    
    private:
        int     imageHeight;        // Rendered image height
        double  pixelSamplesScale;  // Color scale factor for a sum of pixel samples
        point3  center;             // Camera center
        point3  pixel00Loc;         // Location of pixel 0, 0
        vec3    pixelDeltaU;        // Offset to pixel to the right
        vec3    pixelDeltaV;        // Offset to pixel below
        vec3    u, v, w;            // Camera frame basis vectors
        vec3    defocusDiskU;       // Defocus disk horizontal radius
        vec3    defocusDiskV;       // Defocus disk vertical radius
        
        void initialize() {
            imageHeight = int(imageWidth / aspectRatio);
            imageHeight = imageHeight < 1 ? 1 : imageHeight;
            
            pixelSamplesScale = 1.0 / samplesPerPixel;
            
            center = lookFrom;
            
            // Determine viewport dimensions
            auto theta = degreesToRadians(vfov);
            auto h = std::tan(theta / 2);
            auto viewportHeight = 2 * h * focusDist;
            auto viewportWidth = viewportHeight * (double(imageWidth) / imageHeight);
            
            // Calculate the u, v, w unit basis vectors for the camera coordinate frame.
            w = (lookFrom - lookAt).normalize();
            u = (vup.cross(w)).normalize();
            v = w.cross(u);
            
            // Calculate the vectors across the horizontal and down the vertical viewport edges
            auto viewportU = viewportWidth * u;     // Vector across viewport horizontal edge
            auto viewportV = viewportHeight * -v;   // Vector down viewport vertical edge
            
            // Calculate the horizontal and vertical delta vectors from pixel to pixel.
            pixelDeltaU =  viewportU / imageWidth;  //viewportU / imageWidth;
            pixelDeltaV =  viewportV / imageHeight;  //viewportV / imageHeight;
            
            // Calculate the location of the upper left pixel.
            auto viewportUpperLeft = center - (focusDist * w) - viewportU / 2 - viewportV / 2;
            pixel00Loc = viewportUpperLeft + (pixelDeltaU + pixelDeltaV) * 0.5;
            
            // Calculate the camera defocus disk basis vectors
            auto defocusRadius = focusDist * std::tan(degreesToRadians(defocusAngle / 2));
            defocusDiskU = u * defocusRadius;
            defocusDiskV = v * defocusRadius;
        }
    
        ray getRay(int i, int j) const {
            // Construct a camera ray originating from the defocus desk and directed at a randomly sampled
            // point around the pixel location i, j.
            
            auto offset = sampleSquare();
            auto pixelSample = pixel00Loc
                             + (pixelDeltaU * (i + offset.x))
                             + (pixelDeltaV * (j + offset.y));
            
            auto rayOrigin = (defocusAngle <= 0) ? center : defocusDiskSample();
            auto rayDirection = pixelSample - rayOrigin;
            
            return ray(rayOrigin, rayDirection);
                    
        }
    
        vec3 sampleSquare() const {
            // Returns the vector to a random point in the [-.5,-.5]-[+.5,+.5] unit square.
            return vec3(randomDouble() - 0.5, randomDouble() - 0.5, 0);
        }
    
        point3 defocusDiskSample() const {
            // Returns a random point in the camera defocus disk
            auto p = randomInUnitDisk();
            return center + (p.x * defocusDiskU) + (p.y * defocusDiskV);
        }
    
        color rayColor(const ray& r, int depth, const hittable& world) const {
            // If we exceed the ray bounce limit, no more light is gathered.
            if(depth <= 0)
                return color(0, 0, 0);
            
            hitRecord rec;
            
            if(world.hit(r, interval(0.001, infinity), rec)) {
                ray scattered;
                color attenuation;
                if(rec.mat->scatter(r, rec, attenuation, scattered))
                    return attenuation * rayColor(scattered, depth - 1, world);
                return color(0, 0, 0);
            }
            
            vec3 unitDirection = (r.direction()).normalize();
            auto a = 0.5 * (unitDirection.y + 1.0);
            return color(1.0, 1.0, 1.0) * (1 - a) + color(0.5, 0.7, 1.0) * a;
        }
};


#endif /* camera_h */
