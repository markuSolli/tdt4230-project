#include "scene/mesh.h"

#include "scene/obj_loader.h"
#include "math/intersection.h"

Mesh::Mesh(const char* filepath, shared_ptr<Material> _material, point3 position) : mat(_material) {
    vertices = std::vector<vec3>();
    indices = std::vector<vec3i>();
    Interval ix = Interval();
    Interval iy = Interval();
    Interval iz = Interval();

    load_obj(filepath, vertices, indices, ix, iy, iz);

    for (size_t i = 0; i < vertices.size(); i++) {
        vertices[i] += position;
    }

    ix += position.x;
    iy += position.y;
    iz += position.z;

    bbox = AABB(ix, iy, iz);
}

bool Mesh::hit(const Ray &r, Interval ray_t, HitRecord &rec) const {
    if (!bbox.hit(r, ray_t)) {
        return false;
    }

    HitRecord temp_rec;
    bool hit_anything = false;
    double closest_so_far = ray_t.max;

    for (const vec3i tri_indices : indices) {
        if (ray_triangle_intersect(r, Interval(ray_t.min, closest_so_far), temp_rec, vertices[tri_indices.x], vertices[tri_indices.y], vertices[tri_indices.z])) {
            hit_anything = true;
            temp_rec.mat = mat;
            closest_so_far = temp_rec.t;
            rec = temp_rec;
        }
    }

    return hit_anything;
}
