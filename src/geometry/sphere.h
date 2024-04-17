#pragma once

#include <memory>

#include "scene/hittable.h"
#include "render/ray.h"
#include "math/interval.h"
#include "scene/aabb.h"
#include "scene/material.h"

using std::shared_ptr;

class Sphere : public Hittable {
  public:
    Sphere(point3 center, double radius, shared_ptr<Material> material);

    bool hit(const Ray &r, Interval ray_t, HitRecord &rec) const override;

  private:
    point3 center;
    double radius;
    shared_ptr<Material> mat;
    AABB bbox;
};
