#pragma once

#include "math/interval.h"
#include "render/ray.h"
#include "geometry/vec3.h"

class AABB {
  public:
    Interval x, y, z;

    AABB();

    AABB(const Interval& ix, const Interval& iy, const Interval& iz);

    AABB(const point3& a, const point3& b);

    AABB(const AABB& box0, const AABB& box1);

    const Interval& axis(int n) const;

    bool hit(const Ray& r, Interval ray_t) const;
};