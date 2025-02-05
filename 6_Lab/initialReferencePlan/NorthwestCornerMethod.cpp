#include <iostream>
#include <functional>
#include "../variables.h"
#include <iomanip>

typedef std::vector<std::vector<int>> vectorMatrixInt; 

class NorthwestCornerMethod {
public:
  NorthwestCornerMethod() = default;

  void outputResults()
  {
    std::cout << "\n";
    std::cout << "1.1) Метод северо-западного угла\n";
    const int methodResult = result();
    std::cout << "Общая стоимость плана перевозки:\nZ = " << methodResult << "\n";
  }

  vectorMatrixInt getCurrentPlan() {
    return currentPlan;
  }

private:
  vectorMatrixInt currentPlan = {
      {0, 0, 0},
      {0, 0, 0},
      {0, 0, 0}
    };

private:
  void outputCurrentPlan(int i, int j, int productCount) {
    currentPlan[i][j] = productCount;      
    std::cout << "-------------------------\n";
    for(int i = 0; i < currentPlan.size(); i++) {
      std::cout << "| ";
      for(int j = 0; j < currentPlan[i].size(); j++) {
        std::cout << std::setw(5) << currentPlan[i][j] << " | ";
      }
      std::cout << "\n";
    }
    std::cout << "-------------------------\n";

  }
  const int result() {
    vectorMatrixInt deliveryCosts = variables::DELIVERY_COSTS;
    std::vector<int> stocks = variables::STOCKS;
    std::vector<int> needs = variables::NEEDS;
    int result = 0;

    int firstValidColumnInd = 0;
    for (size_t row = 0; row < deliveryCosts.size(); row++) { // по запасам
      for (size_t col = firstValidColumnInd; col < deliveryCosts[row].size(); col++) { // по потребностям
        int quantity = std::min(needs[col], stocks[row]);
        outputCurrentPlan(row, col, quantity);
        result += deliveryCosts[row][col] * quantity;
        stocks[row] -= quantity;
        needs[col] -= quantity;

        if (needs[col] == 0) {
          firstValidColumnInd++;
        }
        if (stocks[row] == 0) {
          goto nextRow;
        }
      }
      nextRow:;
    }
    return result;
  }
};