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
    std::cout << "1) Метод равномерного поиска\n";
    std::cout << "------------------------------------\n";
    std::cout << std::setw(10) << "f(x1, x2)" << " | " << std::setw(10) << "x1" << " | " << std::setw(10) << "x2\n";
    std::cout << "------------------------------------\n";
    std::pair<Point, double> methodResult = result();
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
    Point currentDeltaX = variables::DELTA_X;

    double f_xk = func(basePoint);

    while (true)
    {
      double higher_f_xk = func(basePoint + currentDeltaX);
      double lower_f_xk = func(basePoint - currentDeltaX);
      double next_f_xk = std::min(higher_f_xk, lower_f_xk);
      if (next_f_xk < f_xk)
      {
        basePoint = higher_f_xk < lower_f_xk ? 
          basePoint + currentDeltaX : 
          basePoint - currentDeltaX;
        f_xk = next_f_xk;

        std::cout << std::setprecision(8) << std::setw(10) << f_xk << " | " 
          << std::setw(10) << basePoint.x1 << " | " << std::setw(10) << basePoint.x2 << "\n";
      }
      else
      {
        if(norm(currentDeltaX) < variables::EPS) {
          return std::make_pair(basePoint, f_xk);
        }
        currentDeltaX /= variables::ALPHA;
      }
    }
  }
};