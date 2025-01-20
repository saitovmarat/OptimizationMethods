#include <functional>
#include <iostream>
#include "../variables.h"
#include "../../helpfulFunctions.cpp"
#include "../../myObjects/vector.hpp"
#include "../../myObjects/point.cpp"
#include "../../myObjects/matrix.hpp"

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
    std::cout << "--------------------------------------------\n";
    std::cout << "2) Метод барьерных функций\n"; 
    std::cout << "-----+------------+------------+------------\n";
    std::cout << std::setw(4) << "k" << " | " << std::setw(10) << "x1" << " | " << std::setw(10) << "x2" << " | " << std::setw(10) << "P(X, r^k)" << "\n";
    std::cout << "-----+------------+------------+------------\n";
    const std::pair<Point, double> methodResult = result();
    std::cout << "-----+------------+------------+------------\n";
    std::cout << "Точка минимума X: " << "[" << methodResult.first.coords[0] << "; " << methodResult.first.coords[1] << "]" << "\n";
    std::cout << "Значение функции в этой точке f(X) = " << func(methodResult.first) << "\n\n";
  };    

private:
  double ri = variables::R_02;

  std::function<double(Point)> func;
  std::function<std::vector<double>(Point)> areaRestrictions;
  std::function<double(Point)> funcWithPenalty = {
    [this](Point point) -> double {
      const std::vector<double> area = areaRestrictions(point);
      if(area[0] >= 0 || area[1] >= 0) {
        return float('inf');
      }
      return func(point) + getPenalty(point);
    }
  };

  const double getPenalty(Point point) {
    const std::vector<double> area = areaRestrictions(point);
    return helpfulFunctions::logPenaltyFunc(area, ri);
  }

  const double getStep(Point point, myObjects::Vector<double> gradient) {
    double step = variables::LAMBDA;
    double initialFunc = funcWithPenalty(point);
    while(true) {
      const Point nextPoint = point - gradient * step;
      const double newFunc = funcWithPenalty(nextPoint);
      if(newFunc <= initialFunc - variables::ALPHA * step * gradient.getNorm()) {
        break;
      }
      step *= variables::BETA;
    }
    return step;
  }

private:
  const Point getMinPoint(Point point) {
    Point currentPoint = point;
    const double M = variables::MAX_ITERATIONS_NUM;
    
    for(int k = 1; k <= M; k++) {
      const myObjects::Vector<double> grad_f_x = { 
        helpfulFunctions::getFirstDerivative(funcWithPenalty, currentPoint, 1), 
        helpfulFunctions::getFirstDerivative(funcWithPenalty, currentPoint, 2)
      };
      const double step = getStep(currentPoint, grad_f_x);
      Point nextPoint = currentPoint - grad_f_x * step;
      
      if(abs(funcWithPenalty(nextPoint) - funcWithPenalty(currentPoint)) <= variables::EPS) {
        return nextPoint;
      }

      currentPoint = nextPoint;
    }  
    return Point({0.0, 0.0});
  }
  const std::pair<Point, double> result() {
    const int M = variables::MAX_ITERATIONS_NUM;
    Point currentPoint = variables::START_POINT;
    
    for(int k = 1; k < M; k++) {
      currentPoint = getMinPoint(currentPoint);
      const double penalty = getPenalty(currentPoint);

      std::cout << std::setw(4) << k << " | " << std::setw(10) << currentPoint.coords[0] << " | " << std::setw(10) << currentPoint.coords[1] << " | " << std::setw(10) << abs(penalty) << "\n";

      if(areaRestrictions(currentPoint)[0] <= 0 
        && areaRestrictions(currentPoint)[1] <= 0 
        && abs(penalty) <= variables::EPS) 
      {
        return std::make_pair(currentPoint, abs(penalty));
      }
      ri /= variables::C2;
    }
    throw std::runtime_error("Метод Штрафов не сходится");
  }
};