#pragma once

#include <memory>

#include "hittable.h"
#include "ray.h"
#include "material.h"
#include "interval.h"

using std::shared_ptr;

class Triangle : public Hittable {
  public:
    Triangle(point3 _a, point3 _b, point3 _c, shared_ptr<Material> _material);

    bool hit(const Ray &r, Interval ray_t, HitRecord &rec) const override;

  private:
    point3 a;
    point3 b;
    point3 c;
    shared_ptr<Material> mat;
};
