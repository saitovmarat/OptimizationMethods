#include <functional>
#include "../variables.h"
#include <iostream>

class BarrierFunctionsMethod
{
public:
  BarrierFunctionsMethod(const std::function<double(double, double)>& func) 
  {
    this->func = func;
  };

  void outputResults()
  {
    std::cout << "------------------------------------\n";
    std::cout << "2) Метод барьерных функций\n";
  }

private:
  std::function<double(double, double)> func;
  double result() const {

    return 0.0;
  }
};