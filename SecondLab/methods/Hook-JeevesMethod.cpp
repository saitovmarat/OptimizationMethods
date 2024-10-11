#include <iostream>
#include <functional>
#include <iomanip>
#include <math.h>
#include "../point.cpp"

/// @brief Метод равномерного поиска (прямой) 
/// для нахождения минимума функции одной переменной.
class HookJeevesMethod
{
  public:
    /// @param startPoint начальная точка
    /// @param deltaX шаг вычисления 
    /// @param alpha 
    /// @param eps точность вычисления
    /// @param func функция вида f(x1, x2)
    HookJeevesMethod(Point startPoint, Point deltaX, double alpha, double eps, std::function<double(Point)> func) {
      this->startPoint = startPoint;
      this->deltaX = deltaX;
      this->alpha = alpha;
      this->eps = eps;
      this->func = func;
    }  

    /// @brief Вывод таблицы результатов выполнения метода равномерного поиска
    void outputResults() 
    {
      std::cout << "----------------------------\n";
      std::cout << "1) Метод равномерного поиска\n";
      std::cout << "----------------------------\n";
      std::cout << std::setw(2) << "f(x1, x2)" << " | " << std::setw(10) << "x1"  << " | " << std::setw(10) << "x2\n";
      std::cout << "----------------------------\n";
      std::cout << std::setw(2) << result() << std::endl;
      std::cout << "Точка минимума: " << "x_min" << "\n";
      std::cout << "Значение функции в этой точке = " << "f_min" << "\n\n";  
    }
  private:
    Point startPoint;
    Point deltaX;
    double alpha;
    double eps;
    std::function<double(Point)> func;

    /// @return Норма вектора
    double norm(Point point) {
      return sqrt(point.x1 * point.x1 + point.x2 * point.x2);
    }

    /// @return Точка минимума функции и значение функции в этой точке
    double result() 
    {
      Point basePoint = startPoint;
      Point currentDeltaX = deltaX;
      
      double f_xk = func(basePoint);

      while (norm(currentDeltaX) >= eps)  {
        double next_f_xk = func(basePoint + currentDeltaX);
        if(next_f_xk < f_xk) {
          basePoint += currentDeltaX;
          f_xk = next_f_xk;
        }
        else {
          currentDeltaX /= alpha;
        }
      }

      std::cout << std::setw(10) << basePoint.x1 << " | " << std::setw(10) << basePoint.x2 << "\n";



      return f_xk;
    }
};