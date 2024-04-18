#pragma once

#include "render/ray.h"
#include "scene/hittable.h"
#include "render/color.h"

class Camera {
  public:
    double aspect_ratio = 1.0;
    int image_width = 100;
    int samples_per_pixel = 10;
    int max_depth = 10;
    int fps = 30;
    color background;

    double vfov = 90;
    point3 lookfrom = point3(0,0,-1);
    point3 lookat   = point3(0,0,0);
    vec3   vup      = vec3(0,1,0);

    void render(const Hittable &world, int frame, int n_frames);

  private:
    int    image_height;
    point3 center;
    point3 pixel_upper_left;
    vec3   delta_u;
    vec3   delta_v;
    vec3   n, u, v;

    void initialize();

    Ray get_ray(int i, int j) const;

    vec3 pixel_sample_square() const;

    color ray_color(const Ray &r, int depth, const Hittable &world) const;
};

template<typename ... Args> std::string string_format(const std::string& format, Args ... args);