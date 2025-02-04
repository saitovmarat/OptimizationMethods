#include <iostream>

#include "./initialReferencePlan/NorthwestCornerMethod.cpp"
#include "./initialReferencePlan/MinCostMethod.cpp"

#include "./optimalReferencePlan/HungarianMethod.cpp"
#include "./optimalReferencePlan/PotentialsMethod.cpp"

// Методы нахождения первоначального опорного плана
// 1) Северо-западного угла +
// 2) Минимальной стоимости +
// 3) Двойного предпочтения
// 4) Аппроксимация Фогеля

// Методы нахождения оптимального опорного плана
// 1) Венгерский +
// 2) Потенциалов +
// 3) Дельта-метод


int main() {
  NorthwestCornerMethod().outputResults();
  MinCostMethod().outputResults();

  HungarianMethod().outputResults();
  PotentialsMethod().outputResults();

  return 0;
}