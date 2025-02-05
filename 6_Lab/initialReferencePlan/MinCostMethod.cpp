#include <iostream>
#include <functional>
#include "../variables.h"
#include <iomanip>
#include <algorithm>

typedef std::vector<std::vector<int>> vectorMatrixInt; 

class MinCostMethod {
public:
  MinCostMethod(){}

  void outputResults()
  {
    std::cout << "\n";
    std::cout << "1.2) Метод минимальной стоимости\n";
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

    while (true) {
      int minCost = std::numeric_limits<int>::max();
      int minRow = -1, minCol = -1;
      for (size_t i = 0; i < deliveryCosts.size(); i++) { // по запасам
        for (size_t j = 0; j < deliveryCosts[i].size(); j++) { // по потребностям
          if (stocks[i] > 0 && needs[j] > 0 && deliveryCosts[i][j] < minCost) {
            minCost = deliveryCosts[i][j];
            minRow = i;
            minCol = j;
          }
        }
      }
      // все запасы и потребности закончились
      if (minRow == -1 || minCol == -1) { 
        break;
      }
      int quantity = std::min(stocks[minRow], needs[minCol]);
      outputCurrentPlan(minRow, minCol, quantity);
      result += deliveryCosts[minRow][minCol] * quantity;
      stocks[minRow] -= quantity;
      needs[minCol] -= quantity;
    }
    return result;
  }
};