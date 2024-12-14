#include <functional>
#include <iostream>

class PenaltyFunctionsMethod {
public:
  PenaltyFunctionsMethod(const std::function<double(double, double)>& func) {
    this->func = func;
  }

  void outputResults() {
    std::cout << "------------------------------------\n";
    std::cout << "1) Метод штрафных функций\n";    
  };    

private:
  std::function<double(double, double)> func;
  double result() const {
    
    return 0.0;
  }
};