#include <math.h>
#include "point.cpp"
#include "methods/Hook-JeevesMethod.cpp"
#include "methods/NewtonMethod.cpp"

double func(const Point& point) {
  const double x1 = point.coords[0];
  const double x2 = point.coords[1];
  return 2 * pow(x1 - 1, 2) + pow(x2 - 6, 2);
}


int main()
{
  HookJeevesMethod(func).outputResults();
  NewtonMethod(func).outputResults();

  return 0;
}