#include <iostream>
#include <functional>
#include <iomanip>
#include <math.h>

/// @brief Метод Пауэлла
/// для нахождения минимума функции одной переменной.
class PowellMethod {
  public:
    PowellMethod(int A, int B, std::function<double(double)> f) {
      a_0 = (double)A;
      b_0 = (double)B;
      func = f;
    }  

    void outputResults() {} 

  private:
    double a_0;
    double b_0;
    std::function<double(double)> func;
};