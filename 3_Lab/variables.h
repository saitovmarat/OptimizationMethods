#include "../myObjects/point.cpp"

#ifndef VARIABLES_H
#define VARIABLES_H

namespace variables {
  const double C1 = 8.0;
  const double C2 = 4.0;
  const double R_01 = 1.0;
  const double R_02 = 5.0;
  const double EPS = 0.0001;
  const Point START_POINT = Point({0.0, 0.0});

  const int MAX_ITERATIONS_NUM = 150;
  const double LAMBDA = 10.0;
  const double ALPHA = 0.1; 
  const double BETA = 0.8;
}

#endif // VARIABLES_H