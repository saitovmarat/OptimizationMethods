#include <iostream>

#include "./initialReferencePlan/NorthwestCornerMethod.cpp"
#include "./initialReferencePlan/MinCostMethod.cpp"

#include "./optimalReferencePlan/HungarianMethod.cpp"
#include "./optimalReferencePlan/PotentialsMethod.cpp"

typedef std::vector<std::vector<int>> vectorMatrixInt; 

// Методы нахождения первоначального опорного плана
// 1) Северо-западного угла +
// 2) Минимальной стоимости +
// 3) Двойного предпочтения
// 4) Аппроксимация Фогеля

// Методы нахождения оптимального опорного плана
// 1) Венгерский +
// 2) Потенциалов +
// 3) Дельта-метод

// TODO: Доделать построение цикла

int main() {
  NorthwestCornerMethod startingPlanMethod = NorthwestCornerMethod();
  startingPlanMethod.outputResults();
  MinCostMethod().outputResults();

  HungarianMethod().outputResults();
  PotentialsMethod(startingPlanMethod.getCurrentPlan()).outputResults();

  return 0;
}