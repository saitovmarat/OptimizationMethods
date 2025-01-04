#include <iostream>
#include <functional>
#include "../../point.cpp"
#include "../../helpfulFunctions.cpp"
#include "../variables.h"

typedef std::vector<std::vector<double>> vectorMatrix;
using namespace helpfulFunctions;

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
    double lambda = pow(10, 4);
    const vectorMatrix I = {{1, 0}, {0, 1}};

    for(int k = 0; k <= M; k++) {
      const std::vector<double> grad_f_x = { 
        getFirstDerivative(func, basePoint, 1), 
        getFirstDerivative(func, basePoint, 2)
      };

      std::cout << std::setw(4) << k << " | " << std::setw(12) << basePoint.coords[0] << " | " << std::setw(12) << basePoint.coords[1] << " | ";
      std::cout << std::setw(12) << func(basePoint) << " | " << std::setw(12) << grad_f_x[0] << " | " << std::setw(12) << grad_f_x[1] << " | " << std::setw(12) << getNorm(grad_f_x) << "\n";

      if(getNorm(grad_f_x) < variables::EPS1) {
        return std::make_pair(basePoint, getNorm(grad_f_x));
      }

      const vectorMatrix H_x = getHesseMatrix(func, basePoint);      
      const std::vector<double> sk = 
        productMatrixByVector(
          getInversedMatrix(sumMatrixPerMatrix(H_x, productMatrixByScalar(lambda, I))),
          productVectorByScalar(-1.0, grad_f_x));

      const double f_k = func(basePoint);
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