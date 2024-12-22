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

const std::vector<double> areaRestrictions(const Point& point) {
  const double x1 = point.coords[0];
  const double x2 = point.coords[1];
  return { x1 + x2 - 3, 2*x1 + x2 - 4 };
}

int main() {
  auto start = std::chrono::high_resolution_clock::now();
  
  PenaltyFunctionsMethod(func, areaRestrictions).outputResults();
  BarrierFunctionsMethod(func, areaRestrictions).outputResults();

  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> duration = end - start;
  std::cout << "Время выполнения: " << duration.count() << " секунд" << std::endl;
  return 0;
}