#include "util.h"

#include "color.h"
#include "hittable.h"
#include "hittable_list.h"
#include "sphere.h"

#include <iostream>

color ray_color(const ray &r, const hittable &world) {
    hit_record rec;
    if (world.hit(r, 0, infinity, rec)) {
        return 0.5 * (rec.normal + color(1,1,1));
    }

    vec3 unit_direction = unit_vector(r.direction());
    double a = 0.5*(unit_direction.y() + 1.0);
    return (1.0-a)*color(1.0, 1.0, 1.0) + a*color(0.5, 0.7, 1.0);
}

// Image
const float ASPECT_RATIO = 16.0 / 9.0;
const int IMAGE_WIDTH = 800;
const int IMAGE_HEIGHT = static_cast<int>(IMAGE_WIDTH / ASPECT_RATIO);

// Camera
const float FOCAL_LENGTH = 1.0;
const float VIEWPORT_HEIGHT = 2.0;
const float VIEWPORT_WIDTH = VIEWPORT_HEIGHT * (static_cast<double>(IMAGE_WIDTH)/IMAGE_HEIGHT);

int main() {
    // World
    hittable_list world;

    world.add(make_shared<sphere>(point3(0,0,-1), 0.5));
    world.add(make_shared<sphere>(point3(0,-100.5,-1), 100));

    // Camera
    point3 camera_center = point3(0, 0, 0);

    vec3 viewport_u = vec3(VIEWPORT_WIDTH, 0, 0);
    vec3 viewport_v = vec3(0, -VIEWPORT_HEIGHT, 0);

    vec3 pixel_delta_u = viewport_u / IMAGE_WIDTH;
    vec3 pixel_delta_v = viewport_v / IMAGE_HEIGHT;

    vec3 viewport_upper_left = camera_center - vec3(0, 0, FOCAL_LENGTH) - viewport_u/2 - viewport_v/2;
    vec3 pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

    std::cout << "P3\n" << IMAGE_WIDTH << ' ' << IMAGE_HEIGHT << "\n255\n";

    for (int j = 0; j < IMAGE_HEIGHT; ++j) {
        std::clog << "\rScanlines remaining: " << (IMAGE_HEIGHT - j) << ' ' << std::flush;
        for (int i = 0; i < IMAGE_WIDTH; ++i) {
            point3 pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
            vec3 ray_direction = pixel_center - camera_center;
            ray r(camera_center, ray_direction);

            color pixel_color = ray_color(r, world);
            write_color(std::cout, pixel_color);
        }
    }

    std::clog << "\rDone.                 \n";

    return EXIT_SUCCESS;
}