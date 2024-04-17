#pragma once

#include <vector>

#include "scene/hittable.h"
#include "scene/aabb.h"

class Mesh : public Hittable {
  public:
    Mesh(const char* filepath, shared_ptr<Material> material, point3 position);

    bool hit(const Ray &r, Interval ray_t, HitRecord &rec) const override;

  private:
    std::vector<vec3> vertices;
    std::vector<vec3i> indices;
    shared_ptr<Material> mat;
    AABB bbox;
};