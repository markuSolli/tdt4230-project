#include "interval.h"

#include <cmath>

Interval::Interval() : min(+INF), max(-INF) {}

Interval::Interval(double _min, double _max) : min(_min), max(_max) {}

Interval::Interval(const Interval& a, const Interval& b) : min(fmin(a.min, b.min)), max(fmax(a.max, b.max)) {}

bool Interval::contains(double x) const {
    return min <= x && x <= max;
}

bool Interval::surrounds(double x) const {
    return min < x && x < max;
}

double Interval::clamp(double x) const {
    if (x < min) return min;
    if (x > max) return max;
    return x;
}

double Interval::size() const {
    return max - min;
}

double Interval::midpoint() const {
    return ((max - min) / 2) + min;
}

Interval Interval::expand(double delta) const {
    double padding = delta / 2;
    return Interval(min - padding, max + padding);
}
