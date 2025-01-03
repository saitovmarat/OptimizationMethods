#include <functional>
#include <iostream>
#include <iomanip>
#include "../variables.h"
#include "../helpfulFunctions.cpp"

typedef std::vector<std::vector<double>> vectorMatrix;

class BarrierFunctionsMethod
{
public:
  BarrierFunctionsMethod(
    const std::function<double(Point)>& func, 
    const std::function<std::vector<double>(Point)>& areaRestrictions) 
  {
    this->func = func;
    this->areaRestrictions = areaRestrictions;
  }

  void outputResults() {
    std::cout << "-------------------------------\n";
    std::cout << "2) Метод барьерных функций\n"; 
    std::cout << "-----+------------+------------\n";
    std::cout << std::setw(4) << "k" << " | " << std::setw(10) << "x1" << " | " << std::setw(10) << "x2" << "\n";
    std::cout << "-----+------------+------------\n";
    std::cout << std::setw(4) << 0 << " | " << std::setw(10) << variables::START_POINT.coords[0] << " | " << std::setw(10) << variables::START_POINT.coords[1] << "\n";
    const std::pair<Point, double> methodResult = result();
    std::cout << "-----+------------+------------\n";
    std::cout << "Точка минимума X: " << "[" << methodResult.first.coords[0] << "; " << methodResult.first.coords[1] << "]" << "\n";
    std::cout << "Значение модуля функции ошибки в этой точке |P(X, r^k)| = " << methodResult.second << "\n\n";
  };    

private:
  std::function<double(Point)> func;
  std::function<std::vector<double>(Point)> areaRestrictions;
  std::function<double(Point, double ri)> funcWithPenalty = {
    [this](Point point, double ri) -> double {
      return func(point) - getPenalty(point, ri);
    }
  };

  const double getPenalty(Point point, double ri) const { 
    const std::vector<double> area = areaRestrictions(point);
    const double reversePenaltyResult = ri * helpfulFunctions::reversePenaltyFunc(area);
    return reversePenaltyResult;    
  }

private:
  const std::pair<Point, double> result() const {
    const double M = 300;
    Point basePoint = variables::START_POINT;
    double ri = variables::R_02;
    
    for(int k = 1; k <= M; k++) {
      const std::vector<double> grad_f_x = { 
        helpfulFunctions::getFirstDerivative(funcWithPenalty, basePoint, ri, 1), 
        helpfulFunctions::getFirstDerivative(funcWithPenalty, basePoint, ri, 2)
      };
      const vectorMatrix H_x = helpfulFunctions::getHesseMatrix(funcWithPenalty, basePoint, ri);
      const vectorMatrix inversed_H_x = helpfulFunctions::getInversedMatrix(H_x);

      const double penalty = getPenalty(basePoint, ri);

      if(abs(penalty) <= variables::EPS) 
      {
        return std::make_pair(basePoint, abs(penalty));
      }

      basePoint -= helpfulFunctions::mulptiplyMatrixByVector(inversed_H_x, grad_f_x);
      
      std::cout << std::setw(4) << k << " | " << std::setw(10) << basePoint.coords[0] << " | " << std::setw(10) << basePoint.coords[1] << "\n";

      ri /= variables::C2;
    }  
    throw std::runtime_error("Метод Барьерных функций не сходится");
  }

};