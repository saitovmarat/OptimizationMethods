#include <functional>
#include <iostream>
#include "../variables.h"
#include "../helpfulFunctions.cpp"

/// @brief Метод штрафных функций для нахождения минимума функции двух переменных через метод Ньютона
class PenaltyFunctionsMethod {
public:
  /// @param func функция вида f(x1, x2)
  /// @param isValid функция для определения того, находится ли точка в произвольном множестве
  PenaltyFunctionsMethod(
    const std::function<double(Point)>& func, 
    const std::function<double(Point)>& squareCut) 
  {
    this->func = func;
    this->squareCut = squareCut;
  }

  void outputResults() {
    std::cout << "------------------------------------\n";
    std::cout << "1) Метод штрафных функций\n"; 
    std::cout << "-----+------------+------------\n";
    std::cout << std::setw(4) << "k" << " | " << std::setw(10) << "x1" << " | " << std::setw(10) << "x2" << "\n";
    std::cout << "-----+------------+------------\n";
    const std::pair<Point, double> methodResult = result();
    std::cout << "-----+------------+------------\n";
    std::cout << "Точка минимума X: " << "[" << methodResult.first.coords[0] << "; " << methodResult.first.coords[1] << "]" << "\n";
    std::cout << "Значение нормы градиента в этой точке |∇f(X)| = " << methodResult.second << "\n\n";
  };    

private:
  std::function<double(Point)> func;
  std::function<double(Point)> squareCut;

private:
  const std::pair<Point, double> result() const {
    const double M = 1000;
    Point basePoint = variables::START_POINT;
    double ri = variables::R;
    double squareCutResult = ri * squareCut(basePoint);

    for(int k = 1; k <= M; k++) {
      const std::vector<double> grad_f_x = { 
        helpfulFunctions::getFirstDerivative(func, basePoint, 1), 
        helpfulFunctions::getFirstDerivative(func, basePoint, 2)
      };
      const vectorMatrix H_x = helpfulFunctions::getHesseMatrix(func, basePoint);
      const vectorMatrix inversed_H_x = helpfulFunctions::getInversedMatrix(H_x);
      
      if(helpfulFunctions::getNorm(grad_f_x) < variables::EPS) {
        return std::make_pair(basePoint, helpfulFunctions::getNorm(grad_f_x));
      }

      const double penalty = ri * squareCutResult; 
      basePoint -= helpfulFunctions::mulptiplyMatrixByVector(inversed_H_x, grad_f_x) + penalty;
      
      std::cout << std::setw(4) << k << " | " << std::setw(10) << basePoint.coords[0] << " | " << std::setw(10) << basePoint.coords[1] << "\n";

      squareCutResult = squareCut(basePoint);
      ri = ri / variables::C;
    }  
    throw std::runtime_error("Метод Штрафов не сходится");
  }

};