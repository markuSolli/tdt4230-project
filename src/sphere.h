#pragma once

#include <memory>

#include "hittable.h"
#include "ray.h"
#include "interval.h"
#include "aabb.h"

using std::shared_ptr;

class Sphere : public Hittable {
  public:
    Sphere(point3 _center, double _radius, shared_ptr<Material> _material);

    bool hit(const Ray &r, Interval ray_t, HitRecord &rec) const override;

  private:
    point3 center;
    double radius;
    shared_ptr<Material> mat;
    AABB bbox;
};
