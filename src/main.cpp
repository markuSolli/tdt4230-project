#include <chrono>

#include "hittable_list.h"
#include "sphere.h"
#include "material.h"
#include "camera.h"
#include "mesh.h"

using namespace std::chrono;

int main() {
    HittableList world;

    auto material_ground = make_shared<Lambertian>(color(0.8, 0.8, 0.0));
    auto material_center = make_shared<Lambertian>(color(0.1, 0.2, 0.5));
    auto material_left   = make_shared<Dielectric>(1.5);
    auto material_right  = make_shared<Metal>(color(0.8, 0.6, 0.2), 0.0);
    auto difflight = make_shared<DiffuseLight>(color(4, 4, 4));

    world.add(make_shared<Sphere>(point3( 0.0, -101.0, 0.0), 100.0, material_ground));
    world.add(make_shared<Sphere>(point3( -2.3, 0.0, 0), 1.0, material_left));
    world.add(make_shared<Mesh>("../res/models/suzanne.obj", material_center));
    world.add(make_shared<Sphere>(point3( 2.3, 0.0, 0.0), 1.0, material_right));
    world.add(make_shared<Sphere>(point3( 5.0, 5.0, 5.0), 3.0, difflight));

    Camera cam;

    cam.aspect_ratio      = 16.0 / 9.0;
    cam.image_width       = 360;
    cam.samples_per_pixel = 256;
    cam.max_depth         = 32;
    cam.fps               = 30;

    cam.vfov     = 70;
    cam.lookfrom = point3(0, 0.4, 3.5);
    cam.lookat   = point3(0, 0, 0);
    cam.vup      = vec3(0, 1, 0);
    cam.background = color(0.1, 0.1, 0.5);

    auto start = steady_clock::now();

    cam.render(world, 0, 1);

    auto stop = steady_clock::now();

    double duration = duration_cast<microseconds>(stop - start).count() / 1e6;

    std::clog << "\rFinished in " << duration << " seconds.                                             \n";
}