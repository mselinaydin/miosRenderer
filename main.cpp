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
    
    auto materialGround = make_shared<lambertian>(color(0.8, 0.8, 0.0));
    auto materialCenter = make_shared<lambertian>(color(0.1, 0.2, 0.5));
    auto materialLeft   = make_shared<dielectric>(1.50);
    auto materialBubble = make_shared<dielectric>(1.00 / 1.50);
    auto materialRight  = make_shared<metal>(color(0.8, 0.6, 0.2), 1.0);

    world.add(make_shared<sphere>(point3(0.0,  -100.5, -1.0), 100.0, materialGround));
    world.add(make_shared<sphere>(point3(0.0,   0.0,   -1.2), 0.5,   materialCenter));
    world.add(make_shared<sphere>(point3(-1.0,  0.0,   -1.0), 0.5,   materialLeft));
    world.add(make_shared<sphere>(point3(-1.0,  0.0,   -1.0), 0.4,   materialBubble));
    world.add(make_shared<sphere>(point3(1.0,   0.0,   -1.0), 0.5,   materialRight));
    
    
//    auto R = std::cos(pi / 4);
//
//    auto materialLeft   = make_shared<lambertian>(color(0, 0, 1));
//    auto materialRight  = make_shared<lambertian>(color(1, 0, 0));
//
//    world.add(make_shared<sphere>(point3(-R, 0, -1), R, materialLeft));
//    world.add(make_shared<sphere>(point3( R, 0, -1), R, materialRight));
    
    camera cam;
    
    cam.aspectRatio     = 16.0 / 9.0;
    cam.imageWidth      = 400;
    cam.samplesPerPixel = 100;
    cam.maxDepth        = 50;
    
    cam.vfov        = 20;
    cam.lookFrom    = point3(-2, 2, 1);
    cam.lookAt      = point3(0, 0, -1);
    cam.vup         = vec3(0, 1, 0);
    
    cam.defocusAngle = 10.0;
    cam.focusDist    = 3.4;
    
    cam.render(world);
}
