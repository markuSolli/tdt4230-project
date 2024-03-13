#include "mesh.h"

#include "obj_loader.h"
#include "triangle.h"

Mesh::Mesh(const char* filepath, shared_ptr<Material> _material) : mat(_material) {
    vertices = std::vector<vec3>();
    indices = std::vector<vec3i>();
    load_obj(filepath, vertices, indices);
}

bool Mesh::hit(const Ray &r, Interval ray_t, HitRecord &rec) const {
    HitRecord temp_rec;
    bool hit_anything = false;
    double closest_so_far = ray_t.max;

    for (const vec3i tri_indices : indices) {
        Triangle triangle = Triangle(vertices[tri_indices.x], vertices[tri_indices.y], vertices[tri_indices.z], mat);

        if (triangle.hit(r, Interval(ray_t.min, closest_so_far), temp_rec)) {
            hit_anything = true;
            closest_so_far = temp_rec.t;
            rec = temp_rec;
        }
    }

    return hit_anything;
}