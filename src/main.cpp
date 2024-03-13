#include "hittable_list.h"
#include "sphere.h"
#include "triangle.h"
#include "camera.h"
#include "mesh.h"

int main() {
    HittableList world;

    auto material_ground = make_shared<Lambertian>(color(0.8, 0.8, 0.0));
    auto material_center = make_shared<Lambertian>(color(0.1, 0.2, 0.5));
    auto material_left   = make_shared<Dielectric>(1.5);
    auto material_right  = make_shared<Metal>(color(0.8, 0.6, 0.2), 0.0);

    world.add(make_shared<Sphere>(point3( 0.0, -101.0, 0.0), 100.0, material_ground));
    world.add(make_shared<Mesh>("../res/models/cube.obj", material_center));
    world.add(make_shared<Sphere>(point3(-2.0, 0.0, 0.0),   1.0, material_left));
    world.add(make_shared<Sphere>(point3(-2.0, 0.0, 0.0),  -0.9, material_left));
    world.add(make_shared<Sphere>(point3( 2.0, 0.0, 0.0),   1.0, material_right));

    Camera cam;

    cam.aspect_ratio      = 16.0 / 9.0;
    cam.image_width       = 600;
    cam.samples_per_pixel = 64;
    cam.max_depth         = 128;

    cam.vfov     = 70;
    cam.lookfrom = point3(0, 1.5, 3);
    cam.lookat   = point3(0, 0, 0);
    cam.vup      = vec3(0, 1, 0);

    cam.render(world);
}