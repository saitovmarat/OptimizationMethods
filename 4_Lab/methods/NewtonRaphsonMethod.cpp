#include <iostream>
#include <functional>
#include "../variables.h"
#include "../../helpfulFunctions.cpp"
#include "../../myObjects/point.cpp"
#include "../../myObjects/matrix.hpp"
#include "../../myObjects/vector.hpp"

class NewtonRaphsonMethod {
public:
  NewtonRaphsonMethod(std::function<double(Point)> func)
  {
    this->func = func;
  }

  void outputResults()
  {
    std::cout << "----------------------------------------------------------------------------------------------\n";
    std::cout << "1) Метод Ньютона-Рафсона\n";
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
  const double get_tk(Point point, myObjects::Vector<double> dk) const {
    const double M = variables::maxIterationsNum;
    Point basePoint = point;

    for(int k = 0; k <= M; k++) {
      const myObjects::Vector<double> grad_f_x = { 
        helpfulFunctions::getFirstDerivative(func, basePoint, 1), 
        helpfulFunctions::getFirstDerivative(func, basePoint, 2)
      };
      const myObjects::Matrix<double> H_x = helpfulFunctions::getHesseMatrix(func, basePoint);
      const myObjects::Matrix<double> inversed_H_x = H_x.getInversedMatrix();
      
      if(grad_f_x.getNorm() < variables::EPS1) {
        double d1 = dk[0];
        double d2 = dk[1];
        double x1 = point.coords[0];
        double x2 = point.coords[1];

        double a = 2*d1*d1 + 2*d1*d2 + 5*d2*d2;
        double b = 4*x1*d1 + 2*x1*d2 + 2*x2*d1 + 10*x2*d2 - 2*d1 - 3*d2;
        double c = 2*x1*x1 + 5*x2*x2 + 2*x1*x2 - 2*x1 - 3*x2 - func(basePoint);
        double descr = b*b - 4*a*c;

        if (descr > 0) {  
          double x1 = (-b + sqrt(descr)) / (2*a);
          double x2 = (-b - sqrt(descr)) / (2*a);
          return std::min(x1, x2);
        }
        else if (descr == 0) {
          double x1 = (-b) / (2*a);
          return x1;
        }
        else {
          return 0;
        }
      }

      basePoint -= inversed_H_x * grad_f_x;
    }
    throw std::runtime_error("Функция нахождения tk прошло все итерации");
  }

  /// @return Точка минимума функции и значение нормы градиента в этой точке
  const std::pair<Point, double> result() const {
    const double M = variables::maxIterationsNum;
    Point basePoint = variables::START_POINT;

    for(int k = 0; k <= M; k++) {
      const myObjects::Vector<double> grad_f_x = { 
        helpfulFunctions::getFirstDerivative(func, basePoint, 1), 
        helpfulFunctions::getFirstDerivative(func, basePoint, 2)
      };
      const myObjects::Matrix<double> H_x = helpfulFunctions::getHesseMatrix(func, basePoint);
      const myObjects::Matrix<double> inversed_H_x = H_x.getInversedMatrix();
      
      std::cout << std::setw(4) << k << " | " << std::setw(12) << basePoint.coords[0] << " | " << std::setw(12) << basePoint.coords[1] << " | ";
      std::cout << std::setw(12) << func(basePoint) << " | " << std::setw(12) << grad_f_x[0] << " | " << std::setw(12) << grad_f_x[1] << " | " << std::setw(12) << grad_f_x.getNorm() << "\n";

      if(grad_f_x.getNorm() < variables::EPS1) {
        return std::make_pair(basePoint, grad_f_x.getNorm());
      }

      const myObjects::Vector<double> dk = (inversed_H_x.getDeterminant() > 0)?
        (inversed_H_x * -1.0) * grad_f_x :
        grad_f_x * -1.0;

      const double tk = get_tk(basePoint, dk);
      
      const Point lastPoint = basePoint;
      basePoint += dk * tk;

      if(getNorm(basePoint - lastPoint) <= variables::EPS2 
        && abs(func(basePoint) - func(lastPoint)) <= variables::EPS2) {
        return std::make_pair(basePoint, grad_f_x.getNorm());
      }

    }  
    throw std::runtime_error("Метод Ньютона не сходится");
  }
};