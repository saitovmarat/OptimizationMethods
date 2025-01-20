#ifndef HELPFULFUNCTIONS_H
#define HELPFULFUNCTIONS_H

#include <iostream>
#include <functional>
#include <iomanip>
#include <math.h>
#include <cmath>
#include "./myObjects/point.cpp"
#include "./myObjects/matrix.hpp"

typedef std::vector<std::vector<double>> vectorMatrix;

//TODO: Добавить возможность выбирать очередность переменных по которым идет смешанное диф-ние

namespace helpfulFunctions {
  /// @brief Получение первой производной функции двух переменных по выбранной переменной
  /// @param func функция вида f(x1, x2)
  /// @param point значение двух переменных
  /// @param deravativeVariableInd индекс выбранной переменной 
  /// @return первая производная
  double getFirstDerivative(std::function<double(Point)> func, Point point, int deravativeVariableInd) {
    double x1 = point.coords[0];
    double x2 = point.coords[1];
    double h = 0.1;
    int i = deravativeVariableInd == 1 ? 1 : 0;
    int j = deravativeVariableInd == 2 ? 1 : 0;
    return (func(Point({x1 + h*i, x2 + h*j})) - func(Point({x1 - h*i, x2 - h*j}))) / (2 * h); 
  }


  /// @brief Получение второй производной функции двух переменных по выбранной переменной
  /// @param func функция вида f(x1, x2)
  /// @param point значение двух переменных
  /// @param deravativeVariableInd индекс выбранной переменной 
  /// @return вторая производная
  double getSecondDerivative(std::function<double(Point)> func, Point point, int deravativeVariableInd) {
    double x1 = point.coords[0];
    double x2 = point.coords[1];
    double h = 0.1;
    int i = deravativeVariableInd == 1 ? 1 : 0;
    int j = deravativeVariableInd == 2 ? 1 : 0;
    return (func(Point({x1 - h*i, x2 - h*j})) - 2 * func(Point({x1, x2})) + func(Point({x1 + h*i, x2 + h*j}))) / pow(h, 2); 
  }

  /// @brief Получение второй производной штрафной функции двух переменных по выбранной переменной
  /// @param func функция вида f(x1, x2, ri)
  /// @param point значение двух переменных
  /// @param ri значение штрафа
  /// @param deravativeVariableInd индекс выбранной переменной 
  /// @return вторая производная
  double getSecondDerivative(std::function<double(Point, double)> func, Point point, double ri, int deravativeVariableInd) {
    double x1 = point.coords[0];
    double x2 = point.coords[1];
    double h = 0.1;
    int i = deravativeVariableInd == 1 ? 1 : 0;
    int j = deravativeVariableInd == 2 ? 1 : 0;
    const double result = (func(Point({x1 - h*i, x2 - h*j}), ri) - 2 * func(Point({x1, x2}), ri) + func(Point({x1 + h*i, x2 + h*j}), ri)) / pow(h, 2);
    return result; 
  }

  /// @brief Получение смешанной второй производной функции двух переменных
  /// @param func функция вида f(x1, x2)
  /// @param point значение двух переменных
  /// @return вторая производная
  double getMixedSecondDerivative(std::function<double(Point)> func, Point point) {
    double x1 = point.coords[0];
    double x2 = point.coords[1];
    double h = 0.1;
    return (func(Point({x1 + h, x2 + h})) - func(Point({x1 + h, x2})) - 
            func(Point({x1, x2 + h})) + func(Point({x1, x2}))) / 
            (pow(h, 2)); 
  }

  /// @brief Получение смешанной второй производной штрафной функции двух переменных
  /// @param func функция вида f(x1, x2, ri)
  /// @param point значение двух переменных
  /// @param ri значение штрафа
  /// @return вторая производная
  double getMixedSecondDerivative(std::function<double(Point, double)> func, Point point, double ri) {
    double x1 = point.coords[0];
    double x2 = point.coords[1];
    double h = 0.1;
    return (func(Point({x1 + h, x2 + h}), ri) - func(Point({x1 + h, x2}), ri) - 
            func(Point({x1, x2 + h}), ri) + func(Point({x1, x2}), ri)) /
            (pow(h, 2)); 
  }

  /// @brief Получение матрицы Гессе для функции двух переменных
  /// @param func функция двух переменных
  /// @param point значение двух переменных
  /// @return матрица Гессе
  const vectorMatrix getHesseMatrix(std::function<double(Point)> func, Point point) {
    return {
      { getSecondDerivative(func, point, 1), getMixedSecondDerivative(func, point) },
      { getMixedSecondDerivative(func, point), getSecondDerivative(func, point, 2) }
    };
  }

  /// @brief Получение матрицы Гессе для штрафной функции двух переменных
  /// @param func функция двух переменных со штрафом
  /// @param point значение двух переменных
  /// @param ri значение штрафа
  /// @return матрица Гессе
  const vectorMatrix getHesseMatrix(std::function<double(Point, double)> func, Point point, double ri) {
    const vectorMatrix result = { { getSecondDerivative(func, point, ri, 1), getMixedSecondDerivative(func, point, ri) },
                                  { getMixedSecondDerivative(func, point, ri), getSecondDerivative(func, point, ri, 2) } };
    return result;
  }

  /// @brief Функция для получения обратной матрицы размером 2 на 2
  /// @param matrix матрица размером 2 на 2
  /// @return обратная матрица
  const myObjects::Matrix<double> getInversedMatrix(const myObjects::Matrix<double>& matrix) 
  {
    const double determinant = matrix.getDeterminant();
    if (determinant == 0) {
      return {};
    } 
    return {
      { matrix(1, 1) / determinant, -matrix(0, 1) / determinant },
      { -matrix(1, 0) / determinant, matrix(0, 0) / determinant }
    };
  }

  /// @brief Функция для получения нормы вектора
  /// @param f_x вектор
  /// @return норма вектора
  double getNorm(std::vector<double> f_x) {
    double result = 0;
    for(double f_xi : f_x) {
      result += pow(f_xi, 2);
    }
    return sqrt(result);
  }

  /// @brief Функция для получения штрафа за нарушение ограничений
  /// @param area вектор ограничений
  /// @return штраф
  const double squareCut(const std::vector<double>& area) {
    double areaSum = 0.0;
    for(double area_i : area) {
      areaSum += pow(area_i, 2) + area_i > 0 ? pow(area_i, 2) : 0;
    }
    return areaSum;
  }

  /// @brief Функция для вычисления штрафа за нарушение ограничений,
  ///        используемого в методе барьерных функций.
  /// @param area вектор ограничений
  /// @return штраф
  const double reversePenaltyFunc(const std::vector<double>& area) {
    double areaSum = 0.0;
    for(double area_i : area) {
      areaSum += area_i;
    }
    return 1.0 / areaSum;
  }

  /// @brief Функция для вычисления штрафа за нарушение ограничений,
  ///        используемого в методе барьерных функций.
  /// @param area вектор ограничений
  /// @return штраф
  const double logPenaltyFunc(const std::vector<double>& area, const double ri) {
    if(area[0] >= 0 || area[1] >= 0) {
      return float('inf');
    }
    double penalty = 0.0;
    for(double area_i : area) {
      penalty = -ri * log(-area_i);
    }
    return penalty;
  }

  /// @brief Умножение матриц
  /// @param matrix1 первая матрица
  /// @param matrix2 вторая матрица
  /// @return матрица - результат умножения матриц
  const vectorMatrix productMatrixByMatrix(const vectorMatrix matrix1, const vectorMatrix matrix2) {
    if (matrix1[0].size() != matrix2.size()) {
      throw std::invalid_argument("Размеры матриц не совпадают.");
    }
    vectorMatrix result(matrix1.size(), std::vector<double>(matrix2[0].size(), 0.0));
    for (size_t i = 0; i < matrix1.size(); ++i) {
      for (size_t j = 0; j < matrix2[0].size(); ++j) {
        for (size_t k = 0; k < matrix2.size(); ++k) {
          result[i][j] += matrix1[i][k] * matrix2[k][j];
        }
      }
    }
    return result;
  }

  /// @brief Умножение матрицы на вектор
  /// @param matrix матрица
  /// @param vector вектор
  /// @return вектор - результат умножения матрицы на вектор
  const std::vector<double> productMatrixByVector(const vectorMatrix matrix, const std::vector<double> vector)  
  {
    if (vector.size() != matrix.size()) {
      throw std::invalid_argument("Размер вектора должен совпадать с количеством строк матрицы.");
    }
    std::vector<double> result(matrix[0].size(), 0.0);
    for (size_t i = 0; i < matrix.size(); ++i) {
      for (size_t j = 0; j < matrix[i].size(); ++j) {
        result[j] += vector[i] * matrix[i][j];
      }
    }
    return result;
  }

  /// @brief Умножение матрицы на скаляр
  /// @param scalar cкаляр
  /// @param matrix матрица
  /// @return матрица - результат умножения матрицы на скаляр
  const vectorMatrix productMatrixByScalar(double scalar, const vectorMatrix& matrix) {
    vectorMatrix result = matrix;
    for (size_t i = 0; i < matrix.size(); ++i) {
      for (size_t j = 0; j < matrix[i].size(); ++j) {
        result[i][j] = scalar * matrix[i][j];
      }
    }
    return result;
  }

  /// @brief Сумма матриц
  /// @param matrix1 первая матрица
  /// @param matrix2 вторая матрица
  /// @return матрица - результат сложения матриц
  const vectorMatrix sumMatrixPerMatrix(const vectorMatrix& matrix1, const vectorMatrix& matrix2) {
    if (matrix1.size() != matrix2.size() || matrix1[0].size() != matrix2[0].size()) {
      throw std::invalid_argument("Размеры матриц должны совпадать.");
    }
    vectorMatrix result = matrix1;
    for (size_t i = 0; i < matrix1.size(); ++i) {
      for (size_t j = 0; j < matrix1[i].size(); ++j) {
        result[i][j] = matrix1[i][j] + matrix2[i][j];
      }
    }
    return result;
  }

  /// @brief Умножение вектора на скаляр
  /// @param scalar скаляр
  /// @param vec вектор
  /// @return вектор - результат умножения вектора на скаляр
  const std::vector<double> productVectorByScalar(double scalar, const std::vector<double>& vec) {
    std::vector<double> result(vec.size());
    for (size_t i = 0; i < vec.size(); ++i) {
        result[i] = scalar * vec[i];
    }
    return result;
  }

  
}

#endif