//
//  main.cpp
// 

#include "miosRenderer.h"
#include <vector>
#include "camera.h"
#include "hittable.h"
#include "hittableList.h"
#include "material.h"
#include "sphere.h"


using namespace std;

int main (int argc, char *argv[])
{
    // World
    
    hittableList world;
    
    auto groundMaterial = make_shared<lambertian>(color(0.5, 0.5, 0.5));
    world.add(make_shared<sphere>(point3(0, -1000, 0), 1000, groundMaterial));
    
    for(int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            auto chooseMat = randomDouble();
            point3 center(a + 0.9 * randomDouble(), 0.2, b + 0.9 * randomDouble());

            if((center - point3(4, 0.2, 0)).length() > 0.9) {
                shared_ptr<material> sphereMaterial;

                if(chooseMat < 0.8) {
                    // diffuse
                    auto albedo = color::random() * color::random();
                    sphereMaterial = make_shared<lambertian>(albedo);
                    world.add(make_shared<sphere>(center, 0.2, sphereMaterial));
                }
                else if(chooseMat < 0.95) {
                    // metal
                    auto albedo = color::random(0.5, 1);
                    auto fuzz = randomDouble(0, 0.5);
                    sphereMaterial = make_shared<metal>(albedo, fuzz);
                    world.add(make_shared<sphere>(center, 0.2, sphereMaterial));
                }
                else {
                    // glass
                    sphereMaterial = make_shared<dielectric>(1.5);
                    world.add(make_shared<sphere>(center, 0.2, sphereMaterial));
                }
            }
        }
    }
    
    auto material1 = make_shared<dielectric>(1.5);
    world.add(make_shared<sphere>(point3(0, 1, 0), 1.0, material1));
    
    auto material2 = make_shared<lambertian>(color(0.4, 0.2, 0.1));
    world.add(make_shared<sphere>(point3(-4, 1, 0), 1.0, material2));
    
    auto material3 = make_shared<metal>(color(0.7, 0.6, 0.5), 0.0);
    world.add(make_shared<sphere>(point3(4, 1, 0), 1.0, material3));
    
    camera cam;
    
    cam.aspectRatio     = 16.0 / 9.0;
    cam.imageWidth      = 1200;
//    cam.samplesPerPixel = 500;
    cam.samplesPerPixel = 5;
    cam.maxDepth        = 50;
    
    cam.vfov        = 20;
    cam.lookFrom    = point3(13, 2, 3);
    cam.lookAt      = point3(0, 0, 0);
    cam.vup         = vec3(0, 1, 0);
    
    cam.defocusAngle    = 0.6;
    cam.focusDist       = 10.0;
    
    // Keeping simple scene for debugging purposes
    
//    auto materialGround = make_shared<lambertian>(color(0.8, 0.8, 0.0));
//    auto materialCenter = make_shared<lambertian>(color(0.1, 0.2, 0.5));
//    auto materialLeft   = make_shared<dielectric>(1.50);
//    auto materialBubble = make_shared<dielectric>(1.00 / 1.50);
//    auto materialRight  = make_shared<metal>(color(0.8, 0.6, 0.2), 1.0);
//
//    world.add(make_shared<sphere>(point3(0.0,  -100.5, -1.0), 100.0, materialGround));
//    world.add(make_shared<sphere>(point3(0.0,   0.0,   -1.2), 0.5,   materialCenter));
//    world.add(make_shared<sphere>(point3(-1.0,  0.0,   -1.0), 0.5,   materialLeft));
//    world.add(make_shared<sphere>(point3(-1.0,  0.0,   -1.0), 0.4,   materialBubble));
//    world.add(make_shared<sphere>(point3(1.0,   0.0,   -1.0), 0.5,   materialRight));
//
    
//    auto R = std::cos(pi / 4);
//
//    auto materialLeft   = make_shared<lambertian>(color(0, 0, 1));
//    auto materialRight  = make_shared<lambertian>(color(1, 0, 0));
//
//    world.add(make_shared<sphere>(point3(-R, 0, -1), R, materialLeft));
//    world.add(make_shared<sphere>(point3( R, 0, -1), R, materialRight));
    
//    camera cam;
    
//    cam.aspectRatio     = 16.0 / 9.0;
//    cam.imageWidth      = 400;
//    cam.samplesPerPixel = 100;
//    cam.maxDepth        = 50;
//
//    cam.vfov        = 20;
//    cam.lookFrom    = point3(-2, 2, 1);
//    cam.lookAt      = point3(0, 0, -1);
//    cam.vup         = vec3(0, 1, 0);
//
//    cam.defocusAngle = 10.0;
//    cam.focusDist    = 3.4;
    
    cam.render(world);
}
