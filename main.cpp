//
//  main.cpp
// 

#include "miosRenderer.h"
#include <vector>
#include "camera.h"
#include "hittable.h"
#include "hittableList.h"
#include "sphere.h"


using namespace std;

int main (int argc, char *argv[])
{
    // World
    
    hittableList world;
    
    world.add(make_shared<sphere>(point3(0, 0, -1), 0.5));
    world.add(make_shared<sphere>(point3(0, -100.5, -1), 100));
    
    camera cam;
    
    cam.aspectRatio     = 16.0 / 9.0;
    cam.imageWidth      = 400;
    cam.samplesPerPixel = 100;
    cam.maxDepth        = 50;
    
    cam.render(world);
}
