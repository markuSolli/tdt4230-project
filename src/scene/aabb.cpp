#include "scene/aabb.h"

AABB::AABB() {}

AABB::AABB(const Interval& ix, const Interval& iy, const Interval& iz) : x(ix), y(iy), z(iz) { }

AABB::AABB(const point3& a, const point3& b) {
    x = Interval(fmin(a.x,b.x), fmax(a.x,b.x));
    y = Interval(fmin(a.y,b.y), fmax(a.y,b.y));
    z = Interval(fmin(a.z,b.z), fmax(a.z,b.z));
}

AABB::AABB(const AABB& box0, const AABB& box1) {
    x = Interval(box0.x, box1.x);
    y = Interval(box0.y, box1.y);
    z = Interval(box0.z, box1.z);
}

const Interval& AABB::axis(int n) const {
    if (n == 1) return y;
    if (n == 2) return z;
    return x;
}

bool AABB::hit(const Ray& r, Interval ray_t) const {
    for (int a = 0; a < 3; a++) {
        double invD = 1 / r.direction().get(a);
        double orig = r.origin().get(a);

        double t0 = (axis(a).min - orig) * invD;
        double t1 = (axis(a).max - orig) * invD;

        if (invD < 0)
            std::swap(t0, t1);

        if (t0 > ray_t.min) ray_t.min = t0;
        if (t1 < ray_t.max) ray_t.max = t1;

        if (ray_t.max <= ray_t.min)
            return false;
    }
    
    return true;
}