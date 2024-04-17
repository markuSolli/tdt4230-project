#pragma once

#include <memory>

#include "scene/hittable.h"
#include "render/ray.h"
#include "math/interval.h"
#include "scene/material.h"

using std::shared_ptr;

class Plane : public Hittable {
  public:
    Plane(point3 center, vec3 normal, shared_ptr<Material> material);

    bool hit(const Ray &r, Interval ray_t, HitRecord &rec) const override;

  private:
    point3 center;
    vec3 normal;
    shared_ptr<Material> material;
};
