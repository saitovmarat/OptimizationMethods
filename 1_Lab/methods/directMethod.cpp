#include <iostream>
#include <functional>
#include <iomanip>
#include <math.h>

/// @brief Метод равномерного поиска (прямой) 
/// для нахождения минимума функции одной переменной.
class DirectMethod {
  public:
    /// @param A начальная точка интервала
    /// @param B конечная точка интервала
    /// @param f функция вида f(x)
    DirectMethod(int A, int B, std::function<double(double)> f) {
      a_0 = (double)A;
      b_0 = (double)B;
      func = f;
    }  

    /// @brief Вывод таблицы результатов выполнения метода равномерного поиска
    /// @param n максимальное количество разбиений интервала
    void outputResults(int n) 
    {
      std::cout << "----------------------------\n";
      std::cout << "1) Метод равномерного поиска\n";
      std::cout << "----------------------------\n";
      std::cout << std::setw(2) << "N" << " | " << std::setw(10) << "x_k"  << " | " << std::setw(10) << "f_xk\n";
      std::cout << "----------------------------\n";
      double f_min = std::numeric_limits<double>::max();
      double x_min = std::numeric_limits<double>::max();
      for (int i = 3; i < n; i++) {
        double x, f;
        std::tie(x, f) = directMethodResult(i);
        if (f < f_min) {
          f_min = f;
          x_min = x;
        }
        std::cout << std::setw(2) << i << " | " << std::setw(10) << x << " | " << std::setw(10) << f << "\n";
      }
      std::cout << "Точка минимума: " << x_min << "\n";
      std::cout << "Значение функции в этой точке = " << f_min << "\n\n";  
    }
  private:
    double a_0;
    double b_0;
    std::function<double(double)> func;

    /// @param N количество разбиений интервала
    /// @return Точка минимума функции и значение функции в этой точке
    std::pair<double, double> directMethodResult(int N)
    {
      double x_k = 0;
      double f_min = func(x_k);
      for (int i = 1; i < N; i++)
      {
        double x_i = a_0 + i * ((b_0 - a_0) / (N + 1));
        double f_xi = func(x_i);
        if (f_xi < f_min)
        {
          f_min = f_xi;
          x_k = x_i;
        }
      }
      return std::make_pair(x_k, f_min);
    }
};