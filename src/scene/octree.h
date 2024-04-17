#pragma once

#include <vector>

#include "scene/hittable.h"
#include "scene/aabb.h"

class Octree: public Hittable {
  public:
    Octree(const char* filepath, shared_ptr<Material> _material, size_t limit);

    bool hit(const Ray &r, Interval ray_t, HitRecord &rec) const override;

  private:
    shared_ptr<std::vector<vec3>> vertices;
    std::vector<shared_ptr<Hittable>> nodes;
    shared_ptr<Material> mat;
    AABB bbox;
};

class OctreeNode: public Hittable {
  public:
    OctreeNode(shared_ptr<std::vector<vec3>> vertices, std::vector<vec3i> indices, AABB bbox, size_t limit);

    bool hit(const Ray &r, Interval ray_t, HitRecord &rec) const override;

  private:
    std::vector<shared_ptr<Hittable>> nodes;
    AABB bbox;
};

class OctreeLeaf: public Hittable {
  public:
    OctreeLeaf(shared_ptr<std::vector<vec3>> vertices, std::vector<vec3i> indices, AABB bbox);

    bool hit(const Ray &r, Interval ray_t, HitRecord &rec) const override;

  private:
    shared_ptr<std::vector<vec3>> vertices;
    std::vector<vec3i> indices;
    AABB bbox;
};
