#pragma once

#include "util.h"

class Interval {
  public:
    double min, max;

    Interval();

    Interval(double _min, double _max);

    bool contains(double x) const;

    bool surrounds(double x) const;

    double clamp(double x) const;

    static const Interval empty, universe;
};

const static Interval empty   (+INF, -INF);
const static Interval universe(-INF, +INF);
