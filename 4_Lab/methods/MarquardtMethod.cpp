#include <iostream>
#include <functional>
#include "../../myObjects/vector.hpp"
#include "../../myObjects/matrix.hpp"
#include "../../myObjects/point.cpp"
#include "../../helpfulFunctions.cpp"
#include "../variables.h"

class MarquardtMethod {
public:
  MarquardtMethod(std::function<double(Point)> func)
  {
    this->func = func;
  }

  void outputResults()
  {
    std::cout << "----------------------------------------------------------------------------------------------\n";
    std::cout << "2) Метод Марквардта\n";
    std::cout << "-----+--------------+--------------+--------------+--------------+--------------+-------------\n";
    std::cout << std::setw(4) << "k" << " | " << std::setw(12) << "x1" << " | " << std::setw(12) << "x2" << " | ";
    std::cout << std::setw(12) << "f(x1, x2)" << " | " << std::setw(12) << "∇f(X)[0]" << "   | " << std::setw(12) << "∇f(X)[1]" << "   | " << std::setw(12) << "|∇f(X)|" << "\n";
    std::cout << "-----+--------------+--------------+--------------+--------------+--------------+-------------\n";
    const std::pair<Point, double> methodResult = result();
    std::cout << "-----+--------------+--------------+--------------+--------------+--------------+-------------\n";
    std::cout << "Точка минимума X: " << "[" << methodResult.first.coords[0] << "; " << methodResult.first.coords[1] << "]" << "\n";
    std::cout << "Значение нормы градиента в этой точке |∇f(X)| = " << methodResult.second << "\n\n";
  }

private:
  std::function<double(Point)> func;

private:
  const std::pair<Point, double> result() const {
    const int M = variables::maxIterationsNum;
    Point basePoint = variables::START_POINT;
    double lambda = 1e4;
    const myObjects::Matrix<double> I = {{1.0, 0.0}, {0.0, 1.0}};

    for(int k = 0; k <= M; k++) {
      myObjects::Vector<double> grad_f_x = {
        helpfulFunctions::getFirstDerivative(func, basePoint, 1), 
        helpfulFunctions::getFirstDerivative(func, basePoint, 2)
      };

      std::cout << std::setw(4) << k << " | " << std::setw(12) << basePoint.coords[0] << " | " << std::setw(12) << basePoint.coords[1] << " | ";
      std::cout << std::setw(12) << func(basePoint) << " | " << std::setw(12) << grad_f_x[0] << " | " << std::setw(12) << grad_f_x[1] << " | " << std::setw(12) << grad_f_x.getNorm() << "\n";

      if(grad_f_x.getNorm() < variables::EPS1) {
        return std::make_pair(basePoint, grad_f_x.getNorm());
      }

      const myObjects::Matrix<double> H_x = helpfulFunctions::getHesseMatrix(func, basePoint); 
      const myObjects::Vector<double> sk = 
        (H_x + (I * lambda)).getInversedMatrix() * (grad_f_x * -1.0);

      double f_k = func(basePoint);
      basePoint += Point(sk);

      while(func(basePoint) >= f_k) {
        lambda *= 2.0;
        basePoint += Point(sk);
      }
      
      lambda /= 2.0; 
    }

    throw std::runtime_error("Превышено максимальное количество итераций.");
  }
};