#include <iostream>
#include <math.h>
#include "./methods/BarrierFunctionsMethod.cpp"
#include "./methods/PenaltyFunctionsMethod.cpp"
#include <chrono>

double func(const Point& point) {
  const double x1 = point.coords[0];
  const double x2 = point.coords[1];
  return pow(x1, 2) + pow(x2, 2) - 6*x1 - 3*x2 + 5;
}

const double squareCut(const Point& point) {
  const double x1 = point.coords[0];
  const double x2 = point.coords[1];
  const double result = pow(1/2 * (x1 + x2 -3 + 2*x1 + x2 - 4), 2);
  return result;
}

int main() {
  auto start = std::chrono::high_resolution_clock::now();
  
  PenaltyFunctionsMethod(func, squareCut).outputResults();
  BarrierFunctionsMethod(func).outputResults();

  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> duration = end - start;
  std::cout << "Время выполнения: " << duration.count() << " секунд" << std::endl;
  return 0;
}