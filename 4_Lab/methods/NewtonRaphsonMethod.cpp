#include <iostream>
#include <functional>
#include "../variables.h"
#include "../../helpfulFunctions.cpp"
#include "../../point.cpp"

typedef std::vector<std::vector<double>> vectorMatrix;
using namespace helpfulFunctions;

class NewtonRaphsonMethod {
public:
  NewtonRaphsonMethod(std::function<double(Point)> func)
  {
    this->func = func;
  }

  void outputResults()
  {
    std::cout << "-------------------------------\n";
    std::cout << "1) Метод Ньютона-Рафсона\n";
    std::cout << "-----+------------+------------\n";
    std::cout << std::setw(4) << "k" << " | " << std::setw(10) << "x1" << " | " << std::setw(10) << "x2" << "\n";
    std::cout << "-----+------------+------------\n";
    const std::pair<Point, double> methodResult = result();
    std::cout << "-----+------------+------------\n";
    std::cout << "Точка минимума X: " << "[" << methodResult.first.coords[0] << "; " << methodResult.first.coords[1] << "]" << "\n";
    std::cout << "Значение нормы градиента в этой точке |∇f(X)| = " << methodResult.second << "\n\n";
  }

private:
  std::function<double(Point)> func;

private:
  /// @return Точка минимума функции и значение нормы градиента в этой точке
  const std::pair<Point, double> result() const {
    const double M = variables::maxIterationsNum;
    Point basePoint = variables::START_POINT;

    for(int k = 1; k <= M; k++) {
      const std::vector<double> grad_f_x = { 
        helpfulFunctions::getFirstDerivative(func, basePoint, 1), 
        helpfulFunctions::getFirstDerivative(func, basePoint, 2)
      };
      const vectorMatrix H_x = helpfulFunctions::getHesseMatrix(func, basePoint);
      const vectorMatrix inversed_H_x = helpfulFunctions::getInversedMatrix(H_x);
      
      if(helpfulFunctions::getNorm(grad_f_x) < variables::EPS1) {
        return std::make_pair(basePoint, helpfulFunctions::getNorm(grad_f_x));
      }

      basePoint -= helpfulFunctions::productMatrixByVector(inversed_H_x, grad_f_x);

      std::cout << std::setw(4) << k << " | " << std::setw(10) << basePoint.coords[0] << " | " << std::setw(10) << basePoint.coords[1] << "\n";
    }  
    throw std::runtime_error("Метод Ньютона не сходится");
  }
};