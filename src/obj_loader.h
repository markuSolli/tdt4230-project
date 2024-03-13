#pragma once

#include <vector>

#include "vec3.h"

void load_obj(const char* filepath, std::vector<vec3> &vertices, std::vector<vec3i> &indices);
