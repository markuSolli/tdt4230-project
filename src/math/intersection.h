#pragma once

#include "ray.h"
#include "interval.h"
#include "hittable.h"

bool ray_triangle_intersect(const Ray &r, Interval ray_t, HitRecord &rec, const vec3 &a, const vec3 &b, const vec3 &c);
