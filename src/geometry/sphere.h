#pragma once

#include <memory>

#include "scene/hittable.h"
#include "render/ray.h"
#include "math/interval.h"
#include "scene/aabb.h"
#include "scene/material.h"

using std::shared_ptr;

/**
 * Class that represents a 3D sphere defined by a center and radius.
 */
class Sphere : public Hittable {
  public:
    /** Construct a new Sphere.
    *
    * @param center the center of the sphere.
    * @param radius the radius of the sphere.
    * @param material the objects material.
    */
    Sphere(point3 center, double radius, shared_ptr<Material> material);

    bool hit(const Ray &r, Interval ray_t, HitRecord &rec) const override;

  private:
    point3 center;
    double radius;
    shared_ptr<Material> mat;
    AABB bbox;
};
