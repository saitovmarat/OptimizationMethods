#include <initializer_list>
#include <memory>
#include <iostream>

#ifndef VECTOR_H
#define VECTOR_H

namespace myObjects {
template <typename T> 
class Vector {
private: 
  std::unique_ptr<T[]> arr;
  int capacity;
  int current;

public:
  Vector();
  Vector(int size);
  Vector(const Vector<T>& other);
  Vector(std::initializer_list<T> init);
  virtual ~Vector() = default;

  void push_back(const T& value);
  int size() const;
  int getcapacity();
  void print();
  T getNorm() const;

  T* begin();
  T* end();
  const T* begin() const;
  const T* end() const ;

  T& operator[](int index);
  const T& operator[](int index) const;
  Vector operator*(T scalar) const;
  void resize();
  Vector& operator=(const Vector& other);
  T get(int index);
  T pop();

  
};

template<typename T>
Vector<T>::Vector() : capacity(1), current(0)
{
  arr = std::make_unique<T[]>(capacity);
}

template<typename T>
Vector<T>::Vector(int size) : capacity(size*2), current(size)
{
  arr = std::make_unique<T[]>(capacity);
}

// Copy constructor
template<typename T>
Vector<T>::Vector(const Vector<T>& other) : capacity(other.capacity), current(other.current) {
  arr = std::make_unique<T[]>(capacity); 
  for (int i = 0; i < current; ++i) {
    arr[i] = other.arr[i]; 
  }
}

template<typename T>
void Vector<T>::resize() {
  capacity = (capacity == 0) ? 1 : capacity * 2; 
  std::unique_ptr<T[]> newArr = std::make_unique<T[]>(capacity);
  for (int i = 0; i < current; ++i) {
    newArr[i] = arr[i];
  }
  arr = std::move(newArr); 
}

template<typename T>
Vector<T>& Vector<T>::operator=(const Vector& other) {
  if (this != &other) {
    capacity = other.capacity;
    current = other.current;
    arr = std::make_unique<T[]>(capacity);
    for (int i = 0; i < current; ++i) {
        arr[i] = other.arr[i];
    }
  }
  return *this;
}

template<typename T>
Vector<T>::Vector(std::initializer_list<T> init) : capacity(init.size()), current(init.size()) {
  arr = std::make_unique<T[]>(capacity);
  int index = 0;
  for (const auto& value : init) {
    arr[index++] = value;
  }
}

template<typename T>
void Vector<T>::push_back(const T& value) {
  if (current >= capacity) {
      resize(); 
  }
  arr[current++] = value;
}

template<typename T>
T Vector<T>::get(int index)
{
  if (index < current)
    return arr[index];
  return -1;
}

template<typename T>
T Vector<T>::pop() { 
  if (current == 0)
    return -1;

  current--;
  return arr[current];
}

template<typename T>
int Vector<T>::size() const { return current; }

template<typename T>
int Vector<T>::getcapacity() { return capacity; }

template<typename T>
void Vector<T>::print()
{
  for (int i = 0; i < current; i++) {
    std::cout << arr[i] << " ";
  }
  std::cout << "\n";
}

template<typename T>
T Vector<T>::getNorm() const {
  double result = 0;
  for (int i = 0; i < current; ++i) {
    result += pow(arr[i], 2);
  }
  return sqrt(result);
}

template<typename T>
T& Vector<T>::operator[](int index) {
    if (index < 0 || index >= current) {
        throw std::out_of_range("Index out of range");
    }
    return arr[index];
}

template<typename T>
const T& Vector<T>::operator[](int index) const {
    if (index < 0 || index >= current) {
        throw std::out_of_range("Index out of range");
    }
    return arr[index];
}

template<typename T>
Vector<T> Vector<T>::operator*(T scalar) const {
  Vector result(*this);
  for (int i = 0; i < current; ++i) {
    result.arr[i] = arr[i] * scalar;
  }
  return result;
}

template<typename T>
T* Vector<T>::begin() {
    return arr.get();
}

template<typename T>
T* Vector<T>::end() {
    return arr.get() + current;
}

template<typename T>
const T* Vector<T>::begin() const {
    return arr.get();
}

template<typename T>
const T* Vector<T>::end() const {
    return arr.get() + current;
}

} // namespace myObjects

#endif // VECTOR_H