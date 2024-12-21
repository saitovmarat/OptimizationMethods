#include <math.h>
#include "point.cpp"
#include "methods/Hook-JeevesMethod.cpp"
#include "methods/NewtonMethod.cpp"

#include <chrono>


double func1(const Point& point) {
  const double x1 = point.coords[0];
  const double x2 = point.coords[1];
  return 2 * pow(x1 - 1, 2) + pow(x2 - 6, 2);
}

double func(const Point& point) {
  const double x1 = point.coords[0];
  const double x2 = point.coords[1];
  return pow(sin(x1), 2) + pow(x2, 2) - 6*x1 - 3*x2 + 5;
}


int main()
{
  auto start = std::chrono::high_resolution_clock::now();
  HookJeevesMethod(func).outputResults();
  // NewtonMethod(func).outputResults();
  // Вычисляем продолжительность
  auto end = std::chrono::high_resolution_clock::now();

  std::chrono::duration<double> duration = end - start;
  std::cout << "Время выполнения: " << duration.count() << " секунд" << std::endl;

  return 0;
}