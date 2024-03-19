#pragma once

#include "ray.h"
#include "interval.h"
#include "hittable.h"

bool ray_triangle_intersect(const Ray &r, Interval ray_t, HitRecord &rec, vec3 a, vec3 b, vec3 c);
