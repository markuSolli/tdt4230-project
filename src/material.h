#pragma once

#include "ray.h"
#include "hittable.h"
#include "color.h"

class HitRecord;

class Material {
  public:
    virtual ~Material() = default;

    virtual bool scatter(const Ray &r_in, const HitRecord &rec, color &attenuation, Ray &scattered) const = 0;
    
    virtual color emitted() const {
        return color(0,0,0);
    }
};

class Lambertian : public Material {
  public:
    Lambertian(const color &a);

    bool scatter(const Ray &r_in, const HitRecord &rec, color &attenuation, Ray &scattered) const override;

  private:
    color albedo;
};

class Metal : public Material {
  public:
    Metal(const color &a, double f);

    bool scatter(const Ray &r_in, const HitRecord &rec, color &attenuation, Ray &scattered) const override;

  private:
    color albedo;
    double fuzz;
};

class Dielectric : public Material {
  public:
    Dielectric(color albedo, double index_of_refraction);

    bool scatter(const Ray &r_in, const HitRecord &rec, color &attenuation, Ray &scattered) const override;

  private:
    color albedo;
    double ir;

    static double reflectance(double cosine, double ref_idx);
};

class DiffuseLight : public Material {
  public:
    DiffuseLight(color albedo, double strength);

    bool scatter(const Ray& r_in, const HitRecord& rec, color& attenuation, Ray& scattered) const override;

    color emitted() const override;
  private:
    color albedo;
    double strength;
};
