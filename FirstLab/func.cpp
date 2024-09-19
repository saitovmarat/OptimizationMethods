#include <iostream>
#include <iomanip>
#include <math.h>
#include <map>

#define a 0
#define b 7
#define eps 0.1
#define x0 0

double func(double x)
{
  return pow((x - 2), 2);
}

double derivativeFunc(double x)
{
  return 2 * (x - 2);
}

/// @brief Метод равномерного поиска (прямой) для нахождения минимумы функции одной переменной.
/// @param a_0 начальное приближение
/// @param b_0 конечное приближение
/// @param N количество шагов
/// @return Точка минимума функции
double directMethod(double a_0, double b_0, int N)
{
  double x_k = 0;
  double f_min = func(x_k);
  for (int i = 1; i < N; i++)
  {
    double x_i = a_0 + i * ((b_0 - a_0) / N + 1);
    double f_xi = func(x_i);
    if (f_xi < f_min)
    {
      f_min = f_xi;
      x_k = x_i;
    }
  }
  return x_k;
}


void showDerivativesUsingMethodResult(double k, double z_k, double f_zk) 
{
  std::cout << std::setw(3) << k << " | " << std::setw(8) << z_k << " | " << std::setw(6) << f_zk << std::endl;
}

/// @brief Метод средней точки или поиск Больцано
/// (Метод, основанный на использовании производных)
/// для нахождения минимума функции одной переменной.
/// @param a_0 начальное приближение
/// @param b_0 конечное приближение
/// @return Точка минимума функции
double derivativesUsingMethod(double a_0, double b_0)
{
  int k = 0;
  double f_zk = pow(10, 6);
  double a_k = a_0;
  double b_k = b_0;
  double z_k = 0.0;
  while (abs(f_zk) > eps)
  {
    z_k = (a_k + b_k) / 2;
    f_zk = derivativeFunc(z_k);
    if (f_zk < 0)
    {
      a_k = z_k;
    }
    else if (f_zk > 0)
    {
      b_k = z_k;
    }
    k++;

    showDerivativesUsingMethodResult(k, z_k, f_zk);
  }

  std::cout << "Точка минимума: " << z_k << std::endl;
  return z_k;
}
