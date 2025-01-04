#ifndef VARIABLES_H
#define VARIABLES_H

#include "../point.cpp"

typedef std::vector<std::vector<double>> vectorMatrix;

namespace variables {
  const Point START_POINT = Point({0, 0});
  const double DELTA_X = 2.0;
  const double ALPHA = 2.0;
  const double EPS = 0.0001;
}

#endif