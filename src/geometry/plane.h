#pragma once

#include <memory>

#include "hittable.h"
#include "ray.h"
#include "interval.h"
#include "material.h"

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
