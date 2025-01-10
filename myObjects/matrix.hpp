#include <vector>
#include "./vector.hpp"

#ifndef MATRIX_H
#define MATRIX_H

namespace myObjects {
template<typename T>
class Matrix {
private:
  std::vector<std::vector<T>> mat;
  unsigned rows;
  unsigned cols;

public:
  Matrix();
  Matrix(unsigned _rows, unsigned _cols, const T& _initial);
  Matrix(const Matrix<T>& rhs);
  Matrix(const std::vector<std::vector<T>>& matrix);
  Matrix(std::initializer_list<std::initializer_list<T>> init);
  virtual ~Matrix() = default;

  // Matrix mathematical operations
  Matrix<T>& operator=(const Matrix<T>& rhs);

  // Matrix/scalar operations
  Matrix<T> operator+(const Matrix<T>& rhs) const;
  Matrix<T> operator+(T scalar) const;
  Matrix<T> operator-(const T& rhs);
  Vector<T> operator*(const Vector<T>& vec) const;
  Matrix<T> operator*(const T& rhs) const;
  Matrix<T> operator/(const T& rhs);

  // Matrix/vector operations
  std::vector<T> operator*(const std::vector<T>& rhs);
  std::vector<T> diag_vec();

  // Access the individual elements
  T& operator()(const unsigned& row, const unsigned& col);
  const T& operator()(const unsigned& row, const unsigned& col) const;

  // Access the row and column sizes
  unsigned get_rows() const;
  unsigned get_cols() const;

  double getDeterminant() const;
  Matrix<T> getInversedMatrix() const;
};

template<typename T>
Matrix<T>::Matrix() {
  rows = 0;
  cols = 0;
}

template<typename T>
Matrix<T>::Matrix(unsigned _rows, unsigned _cols, const T& _initial) {
  mat.resize(_rows, std::vector<T>(_cols, _initial));
  rows = _rows;
  cols = _cols;
}

template<typename T>
Matrix<T>::Matrix(const Matrix<T>& rhs) {
  mat = rhs.mat;
  rows = rhs.get_rows();
  cols = rhs.get_cols();
}

template<typename T>
Matrix<T>::Matrix(const std::vector<std::vector<T>>& matrix) 
    : mat(matrix), rows(matrix.size()), cols(matrix.empty() ? 0 : matrix[0].size()) {}


template<typename T>
Matrix<T>::Matrix(std::initializer_list<std::initializer_list<T>> init) {
    for (const auto& row : init) {
        mat.emplace_back(row); 
    }
    rows = mat.size();
    cols = rows > 0 ? mat[0].size() : 0; 
}

template<typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& rhs) {
  if (&rhs == this)
    return *this;

  unsigned new_rows = rhs.get_rows();
  unsigned new_cols = rhs.get_cols();

  mat.resize(new_rows);
  for(unsigned i = 0; i < new_rows; i++) {
    mat[i].resize(new_cols);
  }

  for (unsigned i=0; i<new_rows; i++) {
    for (unsigned j=0; j<new_cols; j++) {
      mat[i][j] = rhs(i, j);
    }
  }
  rows = new_rows;
  cols = new_cols;

  return *this;
}

template<typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T>& rhs) const {
  if (rows != rhs.rows || cols != rhs.cols) {
    throw std::invalid_argument("Matrices must have the same dimensions for addition.");
  }

  Matrix<T> result(mat); 
  for (unsigned i = 0; i < rows; ++i) {
    for (unsigned j = 0; j < cols; ++j) {
      result.mat[i][j] += rhs.mat[i][j]; 
    }
  }
  return result;
}

template<typename T>
Matrix<T> Matrix<T>::operator+(T scalar) const {
  Matrix<T> result(mat);
  for (unsigned i = 0; i < rows; ++i) {
    for (unsigned j = 0; j < cols; ++j) {
        result.mat[i][j] += scalar; 
    }
  }
  return result;
}

template<typename T>
Matrix<T> Matrix<T>::operator*(const T& scalar) const {
  Matrix<T> result(mat);
  for (unsigned i = 0; i < rows; ++i) {
    for (unsigned j = 0; j < cols; ++j) {
      result.mat[i][j] *= scalar;
    }
  }
  return result;
}

template<typename T>
Vector<T> Matrix<T>::operator*(const Vector<T>& vec) const {
  if (cols != vec.size()) {
    throw std::invalid_argument("Matrix columns must match vector size.");
  }

  Vector<T> result(rows);
  for (unsigned i = 0; i < rows; ++i) {
    T sum = 0;
    for (unsigned j = 0; j < cols; ++j) {
        sum += mat[i][j] * vec[j];
    }
    result[i] = sum;
  }
  return result;
}

template<typename T>
T& Matrix<T>::operator()(const unsigned& row, const unsigned& col) {
  return this->mat[row][col];
}

template<typename T>
const T& Matrix<T>::operator()(const unsigned& row, const unsigned& col) const {
  return this->mat[row][col];
}

template<typename T>
unsigned Matrix<T>::get_rows() const {
  return this->rows;
}

template<typename T>
unsigned Matrix<T>::get_cols() const {
  return this->cols;
}

template<typename T>
double Matrix<T>::getDeterminant() const {
  if (rows != 2 || cols != 2) {
    throw std::invalid_argument("Determinant is only defined for 2x2 matrices.");
  }
  return mat[0][0] * mat[1][1] - mat[0][1] * mat[1][0];
}

template<typename T>
Matrix<T> Matrix<T>::getInversedMatrix() const {
  if (rows != 2 || cols != 2) {
    throw std::invalid_argument("Inverse is only defined for 2x2 matrices.");
  }

  T determinant = getDeterminant();
  if (determinant == 0) {
    throw std::invalid_argument("Matrix is singular and cannot be inverted.");
  }

  Matrix<T> inv({
    { mat[1][1] / determinant, -mat[0][1] / determinant },
    { -mat[1][0] / determinant, mat[0][0] / determinant }
  });

  return inv; 
}

} // namespace myObjects

#endif // MATRIX_H