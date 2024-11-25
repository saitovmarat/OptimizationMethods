#ifndef VARIABLES_H
#define VARIABLES_H

#include "point.cpp"

typedef std::vector<std::vector<double>> vectorMatrix;

namespace variables {
  const Point START_POINT = {0, 0};
  const Point DELTA_X = {2, 2};
  const double ALPHA = 2;
  const double EPS = 0.1;
}

#endif