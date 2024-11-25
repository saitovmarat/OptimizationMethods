#include <iostream>
#include <functional>
#include <iomanip>
#include <math.h>
#include "../point.cpp"
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

  /// @brief Вывод таблицы результатов выполнения метода Хука-Дживса
  void outputResults()
  {
    std::cout << "------------------------------------\n";
    std::cout << "1) Метод Хука-Дживса\n";
    std::cout << "------------------------------------\n";
    std::cout << std::setw(10) << "f(x1, x2)" << " | " << std::setw(10) << "x1" << " | " << std::setw(10) << "x2\n";
    std::cout << "------------------------------------\n";
    const std::pair<Point, double> methodResult = result();
    std::cout << "------------------------------------\n";
    std::cout << "Точка минимума (x1, x2): " << "[" << methodResult.first.x1 << "; " << methodResult.first.x2 << "]" << "\n";
    std::cout << "Значение функции в этой точке f(x1, x2) = " << methodResult.second << "\n\n";
  }

private:
  std::function<double(Point)> func;

  /// @return Точка минимума функции и значение функции в этой точке
  const std::pair<Point, double> result()
  {
    Point basePoint = variables::START_POINT;
    double currentDeltaX = variables::DELTA_X.x1;

    double f_basePoint = func(basePoint);

    while (true) {
      Point minPoint = {};
      double minFunc = std::numeric_limits<double>::max();
      for (double dx = -1; dx < 2; dx++) {
        for (double dy = -1; dy < 2; dy++) {
          Point newPoint = {
            dx * currentDeltaX + basePoint.x1, 
            dy * currentDeltaX + basePoint.x2
          };
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
          << std::setw(10) << basePoint.x1 << " | " << std::setw(10) << basePoint.x2 << "\n";
      }
      else {
        if(norm(basePoint - minPoint) < variables::EPS) {
          return std::make_pair(basePoint, f_basePoint);
        }
        currentDeltaX /= variables::ALPHA;
      }
    }
  }
};