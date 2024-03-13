#include <vector>

#include "hittable.h"

class Mesh : public Hittable {
  public:
    Mesh(const char* filepath, shared_ptr<Material> _material);

    bool hit(const Ray &r, Interval ray_t, HitRecord &rec) const override;
  private:
    std::vector<vec3> vertices;
    std::vector<vec3i> indices;
    shared_ptr<Material> mat;
};