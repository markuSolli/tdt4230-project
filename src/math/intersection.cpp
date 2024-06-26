#include "math/intersection.h"

// Möller–Trumbore intersection algorithm
bool ray_triangle_intersect(const Ray &r, Interval ray_t, HitRecord &rec, const vec3 &a, const vec3 &b, const vec3 &c) {
    double epsilon = std::numeric_limits<double>::epsilon();

    vec3 edge1 = b - a;
    vec3 edge2 = c - a;
    vec3 ray_cross_e2 = cross(r.direction(), edge2);
    double det = dot(edge1, ray_cross_e2);

    if (det > -epsilon && det < epsilon) {
        return false;       // Ray is parallell to triangle
    }

    double inv_det = 1.0 / det;
    vec3 s = r.origin() - a;
    double u = inv_det * dot(s, ray_cross_e2);

    if (u < 0 || u > 1) {
        return false;
    }

    vec3 s_cross_e1 = cross(s, edge1);
    double v = inv_det * dot(r.direction(), s_cross_e1);

    if (v < 0 || u + v > 1) {
        return false;
    }

    // Compute t to find intersection point
    double t = inv_det * dot(edge2, s_cross_e1);

    if (!ray_t.surrounds(t)) {
        return false;
    }

    rec.t = t;
    rec.p = r.at(rec.t);
    vec3 outward_normal = unit_vector(cross(edge1, edge2));
    rec.set_face_normal(r, outward_normal);
    return true;
}