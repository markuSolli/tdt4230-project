#pragma once

#include "ray.h"
#include "hittable.h"
#include "color.h"

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
    point3 pixel00_loc;
    vec3   pixel_delta_u;
    vec3   pixel_delta_v;
    vec3   u, v, w;

    void initialize();

    Ray get_ray(int i, int j) const;

    vec3 pixel_sample_square() const;

    color ray_color(const Ray &r, int depth, const Hittable &world) const;
};

template<typename ... Args> std::string string_format(const std::string& format, Args ... args);