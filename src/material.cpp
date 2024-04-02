#include "material.h"

#include "util.h"

Lambertian::Lambertian(const color &a) : albedo(a) {}

bool Lambertian::scatter(const Ray &r_in, const HitRecord &rec, color &attenuation, Ray &scattered) const {
    vec3 scatter_direction = rec.normal + random_unit_vector();

    // Catch bad scatter direction
    if (scatter_direction.near_zero())
        scatter_direction = rec.normal;

    scattered = Ray(rec.p, scatter_direction);
    attenuation = albedo;
    return true;
}

Metal::Metal(const color &a, double f) : albedo(a), fuzz(f < 1 ? f : 1) {}

bool Metal::scatter(const Ray &r_in, const HitRecord &rec, color &attenuation, Ray &scattered) const {
    vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);
    scattered = Ray(rec.p, reflected + fuzz * random_unit_vector());
    attenuation = albedo;
    return (dot(scattered.direction(), rec.normal) > 0);
}

Dielectric::Dielectric(double index_of_refraction) : ir(index_of_refraction) {}

bool Dielectric::scatter(const Ray &r_in, const HitRecord &rec, color &attenuation, Ray &scattered) const {
    attenuation = color(1.0, 1.0, 1.0);
    double refraction_ratio = rec.front_face ? (1.0/ir) : ir;

    vec3 unit_direction = unit_vector(r_in.direction());
    double cos_theta = fmin(dot(-unit_direction, rec.normal), 1.0);
    double sin_theta = sqrt(1.0 - cos_theta*cos_theta);

    bool cannot_refract = refraction_ratio * sin_theta > 1.0;
    vec3 direction;

    if (cannot_refract || reflectance(cos_theta, refraction_ratio) > random_double())
        direction = reflect(unit_direction, rec.normal);
    else
        direction = refract(unit_direction, rec.normal, refraction_ratio);

    scattered = Ray(rec.p, direction);
    return true;
}

double Dielectric::reflectance(double cosine, double ref_idx) {
    // Use Schlick's approximation for reflectance.
    double r0 = (1-ref_idx) / (1+ref_idx);
    r0 = r0*r0;
    return r0 + (1-r0)*pow((1 - cosine),5);
}

DiffuseLight::DiffuseLight(color _color) : c(_color) {}

bool DiffuseLight::scatter(const Ray& r_in, const HitRecord& rec, color& attenuation, Ray& scattered) const {
    return false;
}

color DiffuseLight::emitted() const {
    return c;
}
