#include "./methods/directMethod.cpp"
#include "./methods/powellMethod.cpp"
#include "./methods/midpointMethod.cpp"

#define A 0
#define B 7
#define EPS 0.1
#define X0 0

/// @brief Шаг вычисления производной функции
#define H pow(10, -5)

// TODO: 
// 1) Написать метод Пауэла
// 2) Вручную вывести несколько итераций
// 3) Разобраться в смыслах методов 

double func(double x)
{
  return pow((x - 2), 2);
}

int main() {
  int n = 10;

  DirectMethod(A, B, func).outputResults(n);
  PowellMethod(A, B, func).outputResults();
  MidpointMethod(A, B, EPS, H, func).outputResults();

  return 0;
}