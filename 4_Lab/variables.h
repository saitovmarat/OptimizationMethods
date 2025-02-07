#ifndef VARIABLES_H
#define VARIABLES_H
#include "../myObjects/point.cpp"

namespace variables {
  const double A = 2;
  const double B = 5;
  const Point START_POINT = Point({5.0, 5.0});
  const double EPS1 = 0.0001;
  const double EPS2 = 0.0001;
  const int maxIterationsNum = 150;
}

#endif // VARIABLES_H