#include <iostream>
#include <functional>
#include <iomanip>
#include <math.h>
#include "../point.cpp"
#include "../variables.h"

/// @brief 
class NewtonMethod
{
public:
  /// @param func функция вида f(x1, x2)
  NewtonMethod(std::function<double(Point)> func)
  {
    this->func = func;
  }

  /// @brief 
  void outputResults()
  {
    std::cout << "------------------------------------\n";
    std::cout << "2) Метод Ньютона\n";
    std::cout << "------------------------------------\n";
  }

private:
  std::function<double(Point)> func;

  /// @return 
  double result()
  {
    double eps_1 = variables::EPS;
    double eps_2 = variables::EPS;
    double M = 1000;
    Point basePoint = variables::START_POINT;

    Point grad_f_x = { 
      4 * (basePoint.x1 - 1), 
      2 * (basePoint.x2 - 6)
    };

    double H_x[2][2] = {
      { 4 * basePoint.x1, 0 },
      { 0, 2 * basePoint.x2 }
    };

    return 0.0;
  }
};