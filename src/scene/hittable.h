#pragma once

#include <memory>

#include "math/interval.h"
#include "render/ray.h"
#include "scene/material.h"

using std::shared_ptr;

class Material;

/**
 * Class for holding results when an intersection is found.
 */
class HitRecord {
  public:
    point3 p;
    vec3 normal;
    shared_ptr<Material> mat;
    double t;
    bool front_face;

    /** Sets the face normal equal to +/- outward normal, based on the angle between the ray and the outward normal.
    *
    * @param r the ray.
    * @param outward_normal the normal of the surface hit with a ray.
    */
    void set_face_normal(const Ray &r, const vec3 &outward_normal);
};

/**
 * Virtual class defining a hittable object in the scene.
 */
class Hittable {
  public:
    virtual ~Hittable() = default;

    /** Perform a ray intersection test with this object.
    *
    * @param r the ray.
    * @param ray_t the valid interval for t.
    * @param rec the hit record for this intersection.
    * If the ray intersects with this object the fields in the hit record is altered.
    * 
    * @returns if the ray intersects with this object or not.
    */
    virtual bool hit(const Ray &r, Interval ray_t, HitRecord &rec) const = 0;
};
