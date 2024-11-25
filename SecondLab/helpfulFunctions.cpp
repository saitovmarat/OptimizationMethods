#ifndef HELPFULFUNCTIONS_H
#define HELPFULFUNCTIONS_H

#include <iostream>
#include <functional>
#include <iomanip>
#include <math.h>
#include "./point.cpp"

typedef std::vector<std::vector<double>> vectorMatrix;

namespace helpfulFunctions {
  /// @brief Функция для получения определителя матрицы размером 2 на 2
  /// @param matrix матрица размером 2 на 2
  /// @return определитель матрицы
  double getDeterminant(vectorMatrix matrix) {
    return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
  }

  /// @brief Функция для получения нормы вектора длиной 2
  /// @param f_x вектор длиной 2
  /// @return норма вектора
  double getNorm(std::vector<double> f_x) {
    return sqrt(pow(f_x[0], 2) + pow(f_x[1], 2));
  }

  /// @brief Функция для получения обратной матрицы размером 2 на 2
  /// @param matrix матрица размером 2 на 2
  /// @return обратная матрица
  vectorMatrix getInversedMatrix(vectorMatrix matrix) 
  {
    double determinant = getDeterminant(matrix);
    if (determinant == 0) {
      return {};
    } 
    
    return {
      { matrix[1][1] / determinant, -matrix[0][1] / determinant },
      { -matrix[1][0] / determinant, matrix[0][0] / determinant }
    };
  }

  /// @brief Получение первой производной функции двух переменных по выбранной переменной
  /// @param point значение двух переменных
  /// @param deravativeVariableInd индекс выбранной переменной 
  /// @return первая производная
  double getFirstDerivative(std::function<double(Point)> func, Point point, int deravativeVariableInd) {
    double x1 = point.x1;
    double x2 = point.x2;
    double h = 0.1;
    int i = deravativeVariableInd == 1 ? 1 : 0;
    int j = deravativeVariableInd == 2 ? 1 : 0;
    return (func({x1 + h*i, x2 + h*j}) - func({x1 - h*i, x2 - h*j})) / (2 * h); 
  }

  /// @brief Получение второй производной функции двух переменных по выбранной переменной
  /// @param point значение двух переменных
  /// @param deravativeVariableInd индекс выбранной переменной 
  /// @return вторая производная
  double getSecondDerivative(std::function<double(Point)> func, Point point, int deravativeVariableInd) {
    double x1 = point.x1;
    double x2 = point.x2;
    double h = 0.1;
    int i = deravativeVariableInd == 1 ? 1 : 0;
    int j = deravativeVariableInd == 2 ? 1 : 0;
    return (func({x1 - h*i, x2 - h*j}) - 2 * func({x1, x2}) + func({x1 + h*i, x2 + h*j})) / pow(h, 2); 
  }

  /// @brief Получение матрицы Гессе для функции двух переменных
  /// @param func функция двух переменных
  /// @param point значение двух переменных
  /// @param deravativeVariableInd индекс выбранной переменной 
  /// @return матрица Гессе
  const vectorMatrix getHesseMatrix(std::function<double(Point)> func, Point point) {
    return {
      { getSecondDerivative(func, point, 1), 0 },
      { 0, getSecondDerivative(func, point, 2) }
    };
  }
}

#endif