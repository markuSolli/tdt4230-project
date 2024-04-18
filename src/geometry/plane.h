#pragma once

#include <memory>

#include "scene/hittable.h"
#include "render/ray.h"
#include "math/interval.h"
#include "scene/material.h"

using std::shared_ptr;

/**
 * Class that represents a 3D plane defined by a center and normal.
 */
class Plane : public Hittable {
  public:
    /** Construct a new Plane.
    *
    * @param center the position of the plane.
    * @param normal the surface normal of the plane.
    * @param material the objects material.
    */
    Plane(point3 center, vec3 normal, shared_ptr<Material> material);

    bool hit(const Ray &r, Interval ray_t, HitRecord &rec) const override;

  private:
    point3 center;
    vec3 normal;
    shared_ptr<Material> material;
};
