#include <math.h>
#include "point.cpp"
#include "methods/Hook-JeevesMethod.cpp"
#include "methods/NewtonMethod.cpp"

double func1(const Point& point) {
  const double x1 = point.coords[0];
  const double x2 = point.coords[1];
  return 2 * pow(x1 - 1, 2) + pow(x2 - 6, 2);
}

double func2(const Point& point) {
  const double x1 = point.coords[0];
  const double x2 = point.coords[1];
  return x1 * x1 + x2 * x2 - 6 * x1 - 3 * x2 + 5;
}

int main()
{
  HookJeevesMethod(func2).outputResults();
  NewtonMethod(func2).outputResults();

  return 0;
}