#include "sphere.h"

Sphere::Sphere(point3 _center, double _radius, shared_ptr<Material> _material) : center(_center), radius(_radius), mat(_material) {
    vec3 rvec = vec3(radius, radius, radius);
    bbox = AABB(center - rvec, center + rvec);
}

bool Sphere::hit(const Ray &r, Interval ray_t, HitRecord &rec) const {
    if (!bbox.hit(r, ray_t)) {
        return false;
    }
    
    vec3 oc = r.origin() - center;
    double a = r.direction().length_squared();
    double half_b = dot(oc, r.direction());
    double c = oc.length_squared() - radius*radius;

    double discriminant = half_b*half_b - a*c;
    if (discriminant < 0) return false;
    double sqrtd = sqrt(discriminant);

    // Find the nearest root that lies in the acceptable range.
    double root = (-half_b - sqrtd) / a;
    if (!ray_t.surrounds(root)) {
        root = (-half_b + sqrtd) / a;
        if (!ray_t.surrounds(root))
            return false;
    }

    rec.t = root;
    rec.p = r.at(rec.t);
    vec3 outward_normal = (rec.p - center) / radius;
    rec.set_face_normal(r, outward_normal);
    rec.mat = mat;

    return true;
}
