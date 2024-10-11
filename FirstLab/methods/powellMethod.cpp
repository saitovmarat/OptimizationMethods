#include <iostream>
#include <functional>
#include <iomanip>
#include <math.h>

/// @brief Метод Пауэлла
/// для нахождения минимума функции одной переменной.
class PowellMethod {
  public:
    /// @param A начальная точка интервала
    /// @param B конечная точка интервала
    /// @param EPS точность вычисления
    /// @param SIGMA точность вычисления
    /// @param DELTA_X шаг вычисления производной функции
    /// @param f функция вида f(x)
    PowellMethod(int A, int B, double EPS, double SIGMA, double DELTA_X, std::function<double(double)> f) {
      a_0 = (double)A;
      b_0 = (double)B;
      eps = EPS;
      sigma = SIGMA;
      delta_x = DELTA_X;
      func = f;
    }  

    void outputResults() {
      std::cout << "---------------------------------------------------------------------------------------------------------------\n";
      std::cout << "2) Метод Пауэлла\n";
      std::cout << "---------------------------------------------------------------------------------------------------------------\n";
      std::vector<std::string> headers = {
        "k", "x1", "f_x1", "x2", "f_x2", "x3", "f_x3", "x_new"
      };
      for (size_t i = 0; i < headers.size(); ++i) {
          std::cout << std::setw((i == 0) ? 4 : 12) << headers[i] << " | ";
      }
      std::cout << "\n---------------------------------------------------------------------------------------------------------------\n";
      powellMethodResults();
      std::cout << std::endl;
    } 

  private:
    double a_0;
    double b_0;
    double eps;
    double sigma;
    double delta_x;
    std::function<double(double)> func;

    /// @brief Вывод результатов выполнения метода Пауэлла
    void powellMethodResults() {
      double x1 = 0.0;
      double x2 = 0.0;
      double x3 = 0.0;
      double x_new = 0.0;

      double k = 1;
      while(true) {
        x2 = x1 + delta_x;

        double f_x1 = func(x1);
        double f_x2 = func(x2);

        x3 = f_x1 > f_x2 ? x1 + 2 * delta_x : x1 - delta_x; 
        if (x3 < x1) {
          double temp_x1 = x1;
          x1 = x3;
          x3 = x2;
          x2 = temp_x1;
          f_x1 = func(x1);
          f_x2 = func(x2);
        }

        double f_x3 = func(x3);
        double f_min = std::min(std::min(f_x1, f_x2), f_x3);
        double x_min = f_x3 == f_min ? x3 : f_x2 == f_min ? x2 : x1;

        double a1 = (f_x2 - f_x1) / (x2 - x1);
        double a2 = (1 / (x3 - x2)) * (((f_x3 - f_x1) / (x3 - x1)) - ((f_x2 - f_x1) / (x2 - x1)));
        x_new = ((x2 + x1) / 2) - (a1 / (2 * a2));
        double f_x_new = func(x_new);

        // Вывод промежуточных результатов
        std::vector<double> values = {static_cast<double>(k), x1, f_x1, x2, f_x2, x3, f_x3, x_new};
        for (size_t i = 0; i < values.size(); ++i) {
            std::cout << std::setw((i == 0) ? 4 : 12) << values[i] << " | ";
        }
        std::cout << "\n";
        k++;

        x1 = f_x_new < f_min ? x_new : x_min;

        if (std::abs(f_min - f_x_new) <= eps
          && std::abs(x_min - x_new) <= sigma) 
        {
          std::cout << "Точка минимума функции: " << x_new << std::endl;
          std::cout << "Значение функции в этой точке = " << func(x_new) << std::endl;
          return;
        }

        if(k > 1000) {
          std::cout << "Превышено максимальное количество итерации!" << std::endl;
          return;
        }
      }
    }
};