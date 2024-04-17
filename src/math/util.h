#pragma once

#include <limits>

const double INF = std::numeric_limits<double>::infinity();
const double PI = 3.1415926535897932385;

double degrees_to_radians(double degrees);
double random_double();
double random_double(double min, double max);
