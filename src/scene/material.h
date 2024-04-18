#pragma once

#include "render/ray.h"
#include "scene/hittable.h"
#include "render/color.h"

class HitRecord;

class Material {
  public:
    virtual ~Material() = default;

    virtual bool scatter(const Ray &r_in, const HitRecord &rec, color &attenuation, Ray &scattered) const = 0;
    
    virtual color emitted() const {
        return color(0,0,0);
    }
};

class DiffuseMaterial : public Material {
  public:
    DiffuseMaterial(const color &a);

    bool scatter(const Ray &r_in, const HitRecord &rec, color &attenuation, Ray &scattered) const override;

  private:
    color albedo;
};

class SpecularMaterial : public Material {
  public:
    SpecularMaterial(const color &a, double f);

    bool scatter(const Ray &r_in, const HitRecord &rec, color &attenuation, Ray &scattered) const override;

  private:
    color albedo;
    double fuzz;
};

class RefractiveMaterial : public Material {
  public:
    RefractiveMaterial(color albedo, double index_of_refraction);

    bool scatter(const Ray &r_in, const HitRecord &rec, color &attenuation, Ray &scattered) const override;

  private:
    color albedo;
    double ir;

    static double reflectance(double cosine, double ref_idx);
};

class EmissiveMaterial : public Material {
  public:
    EmissiveMaterial(color albedo, double strength);

    bool scatter(const Ray& r_in, const HitRecord& rec, color& attenuation, Ray& scattered) const override;

    color emitted() const override;
  private:
    color albedo;
    double strength;
};
