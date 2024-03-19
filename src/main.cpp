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
    world.add(make_shared<Sphere>(point3(-2.5, 0.0, 0.0),   1.0, material_left));
    world.add(make_shared<Sphere>(point3(-2.5, 0.0, 0.0),  -0.9, material_left));
    world.add(make_shared<Sphere>(point3( 2.5, 0.0, 0.0),   1.0, material_right));

    Camera cam;

    cam.aspect_ratio      = 16.0 / 9.0;
    cam.image_width       = 30;
    cam.samples_per_pixel = 32;
    cam.max_depth         = 64;
    cam.fps               = 30;

    cam.vfov     = 70;
    cam.lookfrom = point3(0, 1.5, 3);
    cam.lookat   = point3(0, 0, 0);
    cam.vup      = vec3(0, 1, 0);

    int clip_duration = 4;
    int n_frames = clip_duration * cam.fps;

    for (int frame = 0; frame < n_frames; frame++) {
        double t = (2.0 * PI * frame) / n_frames;

        cam.lookfrom = point3(4.0 * sin(t), 1.5, 4.0 * cos(t));

        cam.render(world, frame, n_frames);
    }

    std::clog << "\rDone.                                             \n";
}