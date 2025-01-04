#include <iostream>
#include <functional>
#include <iomanip>
#include <math.h>
#include "../variables.h"

/// @brief Прямой метод нахождения экстремума функции двух переменных
class HookJeevesMethod
{
public:
  /// @param func функция вида f(x1, x2)
  HookJeevesMethod(std::function<double(Point)> func)
  {
    this->func = func;
  }

  void outputResults()
  {
    std::cout << "------------------------------------\n";
    std::cout << "1) Метод Хука-Дживса\n";
    std::cout << "------------------------------------\n";
    std::cout << std::setw(10) << "f(x1, x2)" << " | " << std::setw(10) << "x1" << " | " << std::setw(10) << "x2\n";
    std::cout << "------------------------------------\n";
    const std::pair<Point, double> methodResult = result();
    double x1 = methodResult.first.coords[0];
    double x2 = methodResult.first.coords[1];
    std::cout << "------------------------------------\n";
    std::cout << "Точка минимума (x1, x2): " << "[" << x1 << "; " << x2 << "]" << "\n";
    std::cout << "Значение функции в этой точке f(x1, x2) = " << methodResult.second << "\n\n";
  }

private:
  std::function<double(Point)> func;

  /// @return Точка минимума функции и значение функции в этой точке
  const std::pair<Point, double> result()
  {
    Point basePoint = variables::START_POINT;
    double currentDeltaX = variables::DELTA_X;

    double f_basePoint = func(basePoint);

    while (true) {
      Point minPoint = {};
      double minFunc = std::numeric_limits<double>::max();
      for (double dx = -1; dx < 2; dx++) {
        for (double dy = -1; dy < 2; dy++) {
          Point newPoint({
            dx * currentDeltaX + basePoint.coords[0], 
            dy * currentDeltaX + basePoint.coords[1]
          });
          if (newPoint == basePoint)
            continue;
          
          double newFunc = func(newPoint);
          if (newFunc < minFunc) {
            minPoint = newPoint;
            minFunc = newFunc;
          }
        }
      }
      if(minFunc < f_basePoint) {
        basePoint = minPoint;
        f_basePoint = minFunc;
        std::cout << std::setprecision(8) << std::setw(10) << f_basePoint << " | "
          << std::setw(10) << basePoint.coords[0] << " | " << std::setw(10) << basePoint.coords[1] << "\n";
      }
      else {
        if(getNorm(basePoint - minPoint) < variables::EPS) {
          return std::make_pair(basePoint, f_basePoint);
        }
        currentDeltaX /= variables::ALPHA;
      }
    }
  }
};