#include <functional>
#include "../variables.h"
#include <iostream>

class BarrierFunctionsMethod
{
public:
  BarrierFunctionsMethod(const std::function<double(Point)>& func) 
  {
    this->func = func;
  };

  void outputResults()
  {
    std::cout << "------------------------------------\n";
    std::cout << "2) Метод барьерных функций\n";
    std::cout << "Пока не реализовано\n";
  }

private:
  std::function<double(Point)> func;

  double result() const {

    return 0.0;
  }
};