#include <iostream>
#include <functional>
#include <iomanip>
#include <math.h>

// TODO: придумать нормальное описание параметра функции

/// @brief Метод поиска средней точки или поиск Больцано
/// (Метод, основанный на использовании производных)
/// для нахождения минимума функции одной переменной.
class MidpointMethod {
  public:
    /// @param A начальная точка интервала
    /// @param B конечная точка интервала
    /// @param EPS точность вычисления
    /// @param H шаг вычисления производной функции
    /// @param f функция вида f(x)
    MidpointMethod(int A, int B, double EPS, double H, std::function<double(double)> f) {
      a_0 = (double)A;
      b_0 = (double)B;
      eps = EPS;
      h = H;
      func = f;
    }  

    /// @brief Вывод таблицы результатов выполнения метода поиска средней точки
    void outputResults() 
    {
      std::cout << "------------------------------------------------\n";
      std::cout << "3) Метод поиска средней точки или поиск Больцано\n";
      std::cout << "------------------------------------------------\n";
      std::cout << std::setw(3) << "k" << " | " << std::setw(8) << "z_k" << " | " << std::setw(6) << "f_zk\n";
      std::cout << "------------------------------------------------\n";
      int k = 0;
      double f_zk = std::numeric_limits<double>::max();
      double a_k = a_0;
      double b_k = b_0;
      double z_k = 0.0;
      while (abs(f_zk) > eps)
      {
        k++;
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
        showMidpointMethodIntermediateResult(k, z_k, f_zk);
      }
      std::cout << "Точка минимума функции: " << z_k << std::endl;
      std::cout << "Значение функции в этой точке = " << f_zk << std::endl;;
    } 

  private:
    double a_0;
    double b_0;
    double eps;
    double h;
    std::function<double(double)> func;

    /// @return производная от функции f(x)
    double derivativeFunc(double x)
    {
      return (func(x + h) - func(x - h)) / (2 * h);
    }

    /// @brief Вывод промежуточных результатов выполнения метода поиска средней точки
    void showMidpointMethodIntermediateResult(double k, double z_k, double f_zk) 
    {
      std::cout << std::setw(3) << k << " | " << std::setw(8) << z_k << " | " << std::setw(6) << f_zk << "\n";
    }
};