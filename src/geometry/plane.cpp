#include "geometry/plane.h"

Plane::Plane(point3 _center, vec3 _normal, shared_ptr<Material> _material) : center(_center), normal(_normal), material(_material) {}

bool Plane::hit(const Ray &r, Interval ray_t, HitRecord &rec) const {
    double t =  dot(normal, (center - r.origin())) / dot(normal, r.direction());

    if (t <= 0) return false;

    if (!ray_t.surrounds(t)) return false;

    rec.t = t;
    rec.p = r.at(rec.t);
    rec.set_face_normal(r, normal);
    rec.mat = material;

    return true;
}