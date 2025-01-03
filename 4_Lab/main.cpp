#include <iostream>
#include <math.h>
#include "./point.cpp"
#include "./variables.h"

const double func(const Point& point) {
  const double a = variables::a;
  const double b = variables::b;
  const double x1 = point.coords[0];
  const double x2 = point.coords[1];

  const double result = a*pow(x1, 2) + 2*x1*x2 + b*pow(x2, 2) - 2*x1 - 3*x2;  
  return result;
}

int main() {
  
  return 0;
}