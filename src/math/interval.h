#pragma once

#include "math/util.h"

class Interval {
  public:
    double min, max;

    Interval();

    Interval(double _min, double _max);

    Interval(const Interval& a, const Interval& b);

    Interval& operator+=(const double &d);

    bool contains(double x) const;

    bool surrounds(double x) const;

    double clamp(double x) const;

    double size() const;

    double midpoint() const;

    Interval expand(double delta) const;

    static const Interval empty, universe;
};

const static Interval empty   (+INF, -INF);
const static Interval universe(-INF, +INF);

Interval operator+(const Interval &i, const double &d);
