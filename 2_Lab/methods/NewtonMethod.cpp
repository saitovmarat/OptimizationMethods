#include <functional>
#include <iostream>
#include "../variables.h"
#include "../../helpfulFunctions.cpp"
#include "../../myObjects/vector.hpp"
#include "../../myObjects/point.cpp"
#include "../../myObjects/matrix.hpp"

/// @brief Метод Ньютона для нахождения минимума функции двух переменных 
class NewtonMethod
{
public:
  /// @param func функция вида f(x1, x2)
  NewtonMethod(std::function<double(Point)> func)
  {
    this->func = func;
  }

  void outputResults()
  {
    std::cout << "-------------------------------\n";
    std::cout << "2) Метод Ньютона\n";
    std::cout << "-------------------------------\n";
    std::cout << std::setw(4) << "k" << " | " << std::setw(10) << "x1" << " | " << std::setw(10) << "x2" << "\n";
    std::cout << "-------------------------------\n";
    const std::pair<Point, double> methodResult = result();
    std::cout << "-------------------------------\n";
    std::cout << "Точка минимума X: " << "[" << methodResult.first.coords[0] << "; " << methodResult.first.coords[1] << "]" << "\n";
    std::cout << "Значение нормы градиента в этой точке |∇f(X)| = " << methodResult.second << "\n\n";
  }

private:
  std::function<double(Point)> func;

  /// @return Точка минимума функции и значение нормы градиента в этой точке
  const std::pair<Point, double> result()
  {
    const double M = 1000;
    Point basePoint = variables::START_POINT;

    for(int k = 1; k <= M; k++) {
      const myObjects::Vector<double> grad_f_x = { 
        helpfulFunctions::getFirstDerivative(func, basePoint, 1), 
        helpfulFunctions::getFirstDerivative(func, basePoint, 2)
      };
      const myObjects::Matrix<double> H_x = helpfulFunctions::getHesseMatrix(func, basePoint);
      const myObjects::Matrix<double> inversed_H_x = H_x.getInversedMatrix();
      
      if(grad_f_x.getNorm() < variables::EPS) {
        return std::make_pair(basePoint, grad_f_x.getNorm());
      }

      basePoint -= inversed_H_x * grad_f_x;

      std::cout << std::setw(4) << k << " | " << std::setw(10) << basePoint.coords[0] << " | " << std::setw(10) << basePoint.coords[1] << "\n";
    }  
    throw std::runtime_error("Метод Ньютона не сходится");
  }

};