#include <chrono>

#include "scene/hittable_list.h"
#include "geometry/sphere.h"
#include "scene/material.h"
#include "render/camera.h"
#include "scene/octree.h"
#include "scene/mesh.h"
#include "geometry/plane.h"

using namespace std::chrono;

int main() {
    HittableList world;

    auto material_ground = make_shared<Lambertian>(color(0.8, 0.8, 0.0));
    auto material_table = make_shared<Lambertian>(color(0.351, 0.127, 0.047));
    auto material_plate = make_shared<Lambertian>(color(0.9, 0.9, 0.9));
    auto material_green_glass = make_shared<Dielectric>(color(0.92, 1.0, 0.92), 1.3);
    auto material_blue_glass = make_shared<Dielectric>(color(0.92, 0.92, 1.0), 1.3);
    auto material_bowl = make_shared<Metal>(color(0.8, 0.8, 0.8), 0.5);
    auto material_light = make_shared<DiffuseLight>(color(1.0, 1.0, 1.0), 5.0);

    world.add(make_shared<Plane>(point3(0.0, 0.0, 0.0), vec3(0.0, 1.0, 0.0), material_ground));
    world.add(make_shared<Octree>("../res/models/table.obj", material_table, 3));
    world.add(make_shared<Mesh>("../res/models/plate.obj", material_plate, point3(0.67, 1.0, 0.25)));
    world.add(make_shared<Mesh>("../res/models/plate.obj", material_plate, point3(0.67, 1.0, -0.25)));
    world.add(make_shared<Mesh>("../res/models/plate.obj", material_plate, point3(-0.67, 1.0, 0.25)));
    world.add(make_shared<Mesh>("../res/models/plate.obj", material_plate, point3(-0.67, 1.0, -0.25)));
    world.add(make_shared<Mesh>("../res/models/glass.obj", material_green_glass, point3(0.86, 1.0, 0.1)));
    world.add(make_shared<Mesh>("../res/models/glass.obj", material_blue_glass, point3(0.43, 1.0, -0.13)));
    world.add(make_shared<Mesh>("../res/models/glass.obj", material_blue_glass, point3(-0.43, 1.0, 0.1)));
    world.add(make_shared<Mesh>("../res/models/glass.obj", material_green_glass, point3(-0.86, 1.0, -0.13)));
    world.add(make_shared<Mesh>("../res/models/bowl.obj", material_bowl, point3(0.0, 1.0, 0.0)));
    world.add(make_shared<Sphere>(point3(-10.0, 10.0, 10.0), 6.0, material_light));

    Camera cam;

    cam.aspect_ratio      = 16.0 / 9.0;
    cam.image_width       = 360;
    cam.samples_per_pixel = 128;
    cam.max_depth         = 32;
    cam.fps               = 30;

    cam.vfov     = 70;
    cam.lookfrom = point3(0.6, 1.3, 0.8);
    cam.lookat   = point3(-0.5, 0.4, -2.0);
    cam.vup      = vec3(0, 1, 0);
    cam.background = color(0.1, 0.1, 0.1);

    int n_frames = 1;
    
    auto start = steady_clock::now();

    for (int i=0; i < n_frames; i++) {
        cam.render(world, i, n_frames);
    }

    auto stop = steady_clock::now();

    double duration = duration_cast<microseconds>(stop - start).count() / 1e6;

    std::clog << "\rFinished in " << duration << " seconds.                                             \n";
}