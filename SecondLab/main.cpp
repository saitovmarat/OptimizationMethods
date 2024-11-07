#include <math.h>
#include "point.cpp"
#include "methods/Hook-JeevesMethod.cpp"
#include "methods/NewtonMethod.cpp"

// Hook-Jeeves, Newton

const double func(Point point)
{
  return 2 * pow((point.x1 - 1), 2) + pow((point.x2 - 6), 2);
}

int main()
{
  HookJeevesMethod(func).outputResults();
  NewtonMethod(func).outputResults();

  return 0;
}