#include "scene/octree.h"

#include <memory>

#include "scene/obj_loader.h"
#include "math/intersection.h"

void adjust_bbox(AABB &bbox, std::vector<vec3i> &indices, shared_ptr<std::vector<vec3>> vertices) {
    for (vec3i tri_indices : indices) {
        for (int i = 0; i < 3; i++) {
            vec3 vertex = (*vertices)[tri_indices.get(i)];

            if (vertex.x < bbox.x.min) bbox.x.min = vertex.x;
            if (vertex.x > bbox.x.max) bbox.x.max = vertex.x;
            if (vertex.y < bbox.y.min) bbox.y.min = vertex.y;
            if (vertex.y > bbox.y.max) bbox.y.max = vertex.y;
            if (vertex.z < bbox.z.min) bbox.z.min = vertex.z;
            if (vertex.z > bbox.z.max) bbox.z.max = vertex.z;
        }
    }
}

void split_bbox(AABB &bbox, std::vector<AABB> &bboxes) {
    bboxes.push_back(AABB(Interval(bbox.x.min, bbox.x.midpoint()), Interval(bbox.y.min, bbox.y.midpoint()), Interval(bbox.z.min, bbox.z.midpoint())));
    bboxes.push_back(AABB(Interval(bbox.x.min, bbox.x.midpoint()), Interval(bbox.y.min, bbox.y.midpoint()), Interval(bbox.z.midpoint(), bbox.z.max)));
    bboxes.push_back(AABB(Interval(bbox.x.min, bbox.x.midpoint()), Interval(bbox.y.midpoint(), bbox.y.max), Interval(bbox.z.min, bbox.z.midpoint())));
    bboxes.push_back(AABB(Interval(bbox.x.min, bbox.x.midpoint()), Interval(bbox.y.midpoint(), bbox.y.max), Interval(bbox.z.midpoint(), bbox.z.max)));
    bboxes.push_back(AABB(Interval(bbox.x.midpoint(), bbox.x.max), Interval(bbox.y.min, bbox.y.midpoint()), Interval(bbox.z.min, bbox.z.midpoint())));
    bboxes.push_back(AABB(Interval(bbox.x.midpoint(), bbox.x.max), Interval(bbox.y.min, bbox.y.midpoint()), Interval(bbox.z.midpoint(), bbox.z.max)));
    bboxes.push_back(AABB(Interval(bbox.x.midpoint(), bbox.x.max), Interval(bbox.y.midpoint(), bbox.y.max), Interval(bbox.z.min, bbox.z.midpoint())));
    bboxes.push_back(AABB(Interval(bbox.x.midpoint(), bbox.x.max), Interval(bbox.y.midpoint(), bbox.y.max), Interval(bbox.z.midpoint(), bbox.z.max)));
}

void sort_vertices_into_octree(std::vector<vec3i> &indices, shared_ptr<std::vector<vec3>> vertices, AABB &bbox, std::vector<std::vector<vec3i>> &node_indices) {
    for (int i = 0; i < 8; i++) {
        node_indices.push_back(std::vector<vec3i>());
    }

    for (const vec3i tri_indices : indices) {
        vec3 center = ((*vertices)[tri_indices.x] + (*vertices)[tri_indices.y] + (*vertices)[tri_indices.z]) / 3.0;

        if (center.x < bbox.x.midpoint()) {
            if (center.y < bbox.y.midpoint()) {
                if (center.z < bbox.z.midpoint()) {
                    node_indices[0].push_back(tri_indices);
                } else {
                    node_indices[1].push_back(tri_indices);
                }
            } else {
                if (center.z < bbox.z.midpoint()) {
                    node_indices[2].push_back(tri_indices);
                } else {
                    node_indices[3].push_back(tri_indices);
                }
            }
        } else {
            if (center.y < bbox.y.midpoint()) {
                if (center.z < bbox.z.midpoint()) {
                    node_indices[4].push_back(tri_indices);
                } else {
                    node_indices[5].push_back(tri_indices);
                }
            } else {
                if (center.z < bbox.z.midpoint()) {
                    node_indices[6].push_back(tri_indices);
                } else {
                    node_indices[7].push_back(tri_indices);
                }
            }
        }
    }
}

Octree::Octree(const char* filepath, shared_ptr<Material> _material, size_t limit) : mat(_material) {
    std::vector<vec3> local_vertices = std::vector<vec3>();

    std::vector<vec3i> indices = std::vector<vec3i>();
    Interval ix = Interval();
    Interval iy = Interval();
    Interval iz = Interval();

    load_obj(filepath, local_vertices, indices, ix, iy, iz);

    vertices = std::make_shared<std::vector<vec3>>(local_vertices);

    bbox = AABB(ix, iy, iz);

    std::vector<AABB> node_bbox = std::vector<AABB>();
    split_bbox(bbox, node_bbox);

    std::vector<std::vector<vec3i>> node_indices = std::vector<std::vector<vec3i>>();
    sort_vertices_into_octree(indices, vertices, bbox, node_indices);

    for (int i = 0; i < 8; i++) {
        if (node_indices[i].size() > 0) {
            if (node_indices[i].size() > 10 && limit > 0) {
                nodes.push_back(std::make_shared<OctreeNode>(vertices, node_indices[i], node_bbox[i], limit - 1));
            } else {
                nodes.push_back(std::make_shared<OctreeLeaf>(vertices, node_indices[i], node_bbox[i]));
            }
        }
    }
}

bool Octree::hit(const Ray &r, Interval ray_t, HitRecord &rec) const {
    if (!bbox.hit(r, ray_t)) {
        return false;
    }

    HitRecord temp_rec;
    bool hit_anything = false;
    double closest_so_far = ray_t.max;

    for (const shared_ptr<Hittable> &node : nodes) {
        if (node->hit(r, Interval(ray_t.min, closest_so_far), temp_rec)) {
            hit_anything = true;
            temp_rec.mat = mat;
            closest_so_far = temp_rec.t;
            rec = temp_rec;
        }
    }

    return hit_anything;
}

OctreeNode::OctreeNode(shared_ptr<std::vector<vec3>> _vertices, std::vector<vec3i> indices, AABB _bbox, size_t limit) : bbox(_bbox) {
    adjust_bbox(bbox, indices, _vertices);

    std::vector<AABB> node_bbox = std::vector<AABB>();
    split_bbox(bbox, node_bbox);

    std::vector<std::vector<vec3i>> node_indices = std::vector<std::vector<vec3i>>();
    sort_vertices_into_octree(indices, _vertices, bbox, node_indices);

    for (int i = 0; i < 8; i++) {
        if (node_indices[i].size() > 0) {
            if (node_indices[i].size() > 10 && limit > 0) {
                nodes.push_back(std::make_shared<OctreeNode>(_vertices, node_indices[i], node_bbox[i], limit - 1));
            } else {
                nodes.push_back(std::make_shared<OctreeLeaf>(_vertices, node_indices[i], node_bbox[i]));
            }
        }
    }
}

bool OctreeNode::hit(const Ray &r, Interval ray_t, HitRecord &rec) const {
    if (!bbox.hit(r, ray_t)) {
        return false;
    }

    HitRecord temp_rec;
    bool hit_anything = false;
    double closest_so_far = ray_t.max;

    for (const shared_ptr<Hittable> &node : nodes) {
        if (node->hit(r, Interval(ray_t.min, closest_so_far), temp_rec)) {
            hit_anything = true;
            closest_so_far = temp_rec.t;
            rec = temp_rec;
        }
    }

    return hit_anything;
}

OctreeLeaf::OctreeLeaf(shared_ptr<std::vector<vec3>> _vertices, std::vector<vec3i> _indices, AABB _bbox) : vertices(_vertices), indices(_indices), bbox(_bbox) {
    adjust_bbox(bbox, indices, vertices);
}

bool OctreeLeaf::hit(const Ray &r, Interval ray_t, HitRecord &rec) const {
    if (!bbox.hit(r, ray_t)) {
        return false;
    }

    HitRecord temp_rec;
    bool hit_anything = false;
    double closest_so_far = ray_t.max;

    for (const vec3i tri_indices : indices) {
        if (ray_triangle_intersect(r, Interval(ray_t.min, closest_so_far), temp_rec, (*vertices)[tri_indices.x], (*vertices)[tri_indices.y], (*vertices)[tri_indices.z])) {
            hit_anything = true;
            closest_so_far = temp_rec.t;
            rec = temp_rec;
        }
    }

    return hit_anything;
}
