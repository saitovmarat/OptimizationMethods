#include <iostream>
#include <functional>
#include "../variables.h"
#include <iomanip>
#include <algorithm>

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

private:
  void outputTable(int i, int j, int productCount, vectorMatrixInt& currentTable) {
    currentTable[i][j] = productCount;      
    std::cout << "-------------------------\n";
    for(int i = 0; i < currentTable.size(); i++) {
      std::cout << "| ";
      for(int j = 0; j < currentTable[i].size(); j++) {
        std::cout << std::setw(5) << currentTable[i][j] << " | ";
      }
      std::cout << "\n";
    }
    std::cout << "-------------------------\n";

  }
  const int result() {
    vectorMatrixInt currentTable = {
      {0, 0, 0},
      {0, 0, 0},
      {0, 0, 0}
    };
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
      outputTable(minRow, minCol, quantity, currentTable);
      result += deliveryCosts[minRow][minCol] * quantity;
      stocks[minRow] -= quantity;
      needs[minCol] -= quantity;
    }
    return result;
  }
};