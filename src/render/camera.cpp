#include "render/camera.h"

#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <stdexcept>

#include "math/util.h"
#include "math/interval.h"
#include "scene/material.h"

void Camera::render(const Hittable &world, int frame, int n_frames) {
    initialize();

    std::ofstream outfile;
    outfile.open(string_format("data/frames/%.5d.ppm", frame), std::ios::binary);

    outfile << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = 0; j < image_height; ++j) {
        std::clog << "\rFrames remaining: " << (n_frames - frame) << ", Scanlines remaining: " << (image_height - j) << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i) {
            double pixel_red = 0.0;
            double pixel_green = 0.0;
            double pixel_blue = 0.0;

            #pragma omp parallel for reduction(+ : pixel_red, pixel_green, pixel_blue)
            for (int sample = 0; sample < samples_per_pixel; ++sample) {
                Ray r = get_ray(i, j);
                color local_color = ray_color(r, max_depth, world);
                pixel_red += local_color.x;
                pixel_green += local_color.y;
                pixel_blue += local_color.z;
            }

            color pixel_color = color(pixel_red, pixel_green, pixel_blue);
            write_color(outfile, pixel_color, samples_per_pixel);
        }
    }

    outfile.close();
}

void Camera::initialize() {
    image_height = static_cast<int>(image_width / aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height;

    center = lookfrom;

    // Determine viewport dimensions.
    double focal_length = (lookfrom - lookat).length();
    double theta = degrees_to_radians(vfov);
    double h = tan(theta/2);
    double viewport_height = 2 * h * focal_length;
    double viewport_width = viewport_height * (static_cast<double>(image_width)/image_height);

    // Calculate the u,v,w unit basis vectors for the camera coordinate frame.
    n = unit_vector(lookfrom - lookat);
    u = unit_vector(cross(vup, n));
    v = cross(n, u);

    // Calculate the vectors across the horizontal and down the vertical viewport edges.
    vec3 viewport_u = viewport_width * u;
    vec3 viewport_v = viewport_height * -v;

    // Calculate the horizontal and vertical delta vectors from pixel to pixel.
    delta_u = viewport_u / image_width;
    delta_v = viewport_v / image_height;

    // Calculate the location of the upper left pixel.
    vec3 viewport_upper_left = center - (focal_length * n) - viewport_u/2 - viewport_v/2;
    pixel_upper_left = viewport_upper_left + 0.5 * (delta_u + delta_v);
}

Ray Camera::get_ray(int i, int j) const {
    // Get a randomly sampled camera ray for the pixel at location i,j.
    point3 pixel_sample = pixel_upper_left + (i * delta_u) + (j * delta_v) + pixel_sample_square();

    point3 ray_origin = center;
    vec3 ray_direction = pixel_sample - ray_origin;

    return Ray(ray_origin, ray_direction);
}

vec3 Camera::pixel_sample_square() const {
    // Returns a random point in the square surrounding a pixel at the origin.
    double px = -0.5 + random_double();
    double py = -0.5 + random_double();
    return (px * delta_u) + (py * delta_v);
}

color Camera::ray_color(const Ray &r, int depth, const Hittable &world) const {
    HitRecord rec;

    // If we've exceeded the ray bounce limit, no more light is gathered.
    if (depth <= 0)
        return color(0,0,0);
    
    // If the ray hits nothing, return the background color.
    if (!world.hit(r, Interval(0.001, INF), rec))
        return background;
    
    Ray scattered;
    color attenuation;
    color color_from_emission = rec.mat->emitted();

    if (!rec.mat->scatter(r, rec, attenuation, scattered))
        return color_from_emission;
    
    color color_from_scatter = attenuation * ray_color(scattered, depth-1, world);
    return color_from_emission + color_from_scatter;
}

template<typename ... Args>
std::string string_format( const std::string& format, Args ... args) {
    int size_s = std::snprintf( nullptr, 0, format.c_str(), args ... ) + 1; // Extra space for '\0'
    if( size_s <= 0 ){ throw std::runtime_error( "Error during formatting." ); }
    auto size = static_cast<size_t>( size_s );
    std::unique_ptr<char[]> buf( new char[ size ] );
    std::snprintf( buf.get(), size, format.c_str(), args ... );
    return std::string( buf.get(), buf.get() + size - 1 ); // We don't want the '\0' inside
}
