#pragma once

#include <vector>

#include "vec3.h"
#include "interval.h"

void load_obj(const char* filepath, std::vector<vec3> &vertices, std::vector<vec3i> &indices, Interval &ix, Interval &iy, Interval &iz);