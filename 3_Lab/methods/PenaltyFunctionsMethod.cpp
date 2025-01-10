#include <functional>
#include <iostream>
#include "../variables.h"
#include "../../helpfulFunctions.cpp"
#include "../../myObjects/vector.hpp"
#include "../../myObjects/point.cpp"
#include "../../myObjects/matrix.hpp"

/// @brief Метод штрафных функций для нахождения минимума функции двух переменных через метод Ньютона
class PenaltyFunctionsMethod {
public:
  /// @param func функция вида f(x1, x2)
  /// @param isValid функция для определения того, находится ли точка в произвольном множестве
  PenaltyFunctionsMethod(
    const std::function<double(Point)>& func, 
    const std::function<std::vector<double>(Point)>& areaRestrictions) 
  {
    this->func = func;
    this->areaRestrictions = areaRestrictions;
  }

  void outputResults() {
    std::cout << "--------------------------------------------\n";
    std::cout << "1) Метод штрафных функций\n"; 
    std::cout << "-----+------------+------------+------------\n";
    std::cout << std::setw(4) << "k" << " | " << std::setw(10) << "x1" << " | " << std::setw(10) << "x2" << " | " << std::setw(10) << "P(X, r^k)" << "\n";
    std::cout << "-----+------------+------------+------------\n";
    const std::pair<Point, double> methodResult = result();
    std::cout << "-----+------------+------------+------------\n";
    std::cout << "Точка минимума X: " << "[" << methodResult.first.coords[0] << "; " << methodResult.first.coords[1] << "]" << "\n";
    std::cout << "Значение модуля функции ошибки в этой точке |P(X, r^k)| = " << methodResult.second << "\n\n";
  };    

private:
  std::function<double(Point)> func;
  std::function<std::vector<double>(Point)> areaRestrictions;
  std::function<double(Point, double ri)> funcWithPenalty = {
    [this](Point point, double ri) -> double {
      return func(point) + getPenalty(point, ri);
    }
  };

  const double getPenalty(Point point, double ri) const {
    const std::vector<double> area = areaRestrictions(point);
    const double squareCutResult = 0.5 * ri * helpfulFunctions::squareCut(area);
    return squareCutResult;
  }

private:
  const std::pair<Point, double> result() const {
    const double M = 300;
    Point basePoint = variables::START_POINT;
    double ri = variables::R_01;
    
    for(int k = 1; k <= M; k++) {
      const myObjects::Vector<double> grad_f_x = { 
        helpfulFunctions::getFirstDerivative(funcWithPenalty, basePoint, ri, 1), 
        helpfulFunctions::getFirstDerivative(funcWithPenalty, basePoint, ri, 2)
      };
      const myObjects::Matrix<double> H_x = helpfulFunctions::getHesseMatrix(funcWithPenalty, basePoint, ri);
      const myObjects::Matrix<double> inversed_H_x = H_x.getInversedMatrix();

      const double penalty = getPenalty(basePoint, ri);

      std::cout << std::setw(4) << k << " | " << std::setw(10) << basePoint.coords[0] << " | " << std::setw(10) << basePoint.coords[1] << " | " << std::setw(10) << abs(penalty) << "\n";

      if(abs(penalty) <= variables::EPS) {
        return std::make_pair(basePoint, abs(penalty));
      }

      basePoint -= inversed_H_x * grad_f_x;
      ri *= variables::C1;
    }  
    throw std::runtime_error("Метод Штрафов не сходится");
  }
};