#include <iostream>
#include <functional>
#include "../variables.h"
#include <iomanip>

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

    int firstValidColumnInd = 0;
    for (size_t i = 0; i < deliveryCosts.size(); i++) { // по запасам
      for (size_t j = firstValidColumnInd; j < deliveryCosts[i].size(); j++) { // по потребностям
        int quantity = std::min(needs[j], stocks[i]);
        outputTable(i, j, quantity, currentTable);
        result += deliveryCosts[i][j] * quantity;
        stocks[i] -= quantity;
        needs[j] -= quantity;

        if (needs[j] == 0) {
          firstValidColumnInd++;
        }
        if (stocks[i] == 0) {
          goto nextIteration;
        }
      }
      nextIteration:;
    }
    return result;
  }
};