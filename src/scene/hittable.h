#pragma once

#include <memory>

#include "math/interval.h"
#include "render/ray.h"
#include "scene/material.h"

using std::shared_ptr;

class Material;

class HitRecord {
  public:
    point3 p;
    vec3 normal;
    shared_ptr<Material> mat;
    double t;
    bool front_face;

    void set_face_normal(const Ray &r, const vec3 &outward_normal);
};

class Hittable {
  public:
    virtual ~Hittable() = default;

    virtual bool hit(const Ray &r, Interval ray_t, HitRecord &rec) const = 0;
};
