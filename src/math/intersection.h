#pragma once

#include "render/ray.h"
#include "math/interval.h"
#include "scene/hittable.h"

bool ray_triangle_intersect(const Ray &r, Interval ray_t, HitRecord &rec, const vec3 &a, const vec3 &b, const vec3 &c);
