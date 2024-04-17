#pragma once

#include "geometry/vec3.h"

using point3 = vec3;

class Ray {
  public:
    Ray();

    Ray(const point3 &origin, const vec3 &direction);

    point3 origin() const;
    vec3 direction() const;

    point3 at(float t) const;

  private:
    point3 orig;
    vec3 dir;
};
