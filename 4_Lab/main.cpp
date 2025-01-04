#include <iostream>
#include <math.h>
#include <chrono>
#include "../point.cpp"
#include "./variables.h"
#include "./methods/MarquardtMethod.cpp"
#include "./methods/NewtonRaphsonMethod.cpp"

const double func(const Point& point) {
  const double a = variables::A;
  const double b = variables::B;
  const double x1 = point.coords[0];
  const double x2 = point.coords[1];

  const double result = a*pow(x1, 2) + 2*x1*x2 + b*pow(x2, 2) - 2*x1 - 3*x2;  
  return result;
}

int main() {
  auto start = std::chrono::high_resolution_clock::now();

  NewtonRaphsonMethod(func).outputResults();
  MarquardtMethod(func).outputResults();

  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> duration = end - start;
  std::cout << "Время выполнения: " << duration.count() << " секунд" << std::endl;
  return 0;
}