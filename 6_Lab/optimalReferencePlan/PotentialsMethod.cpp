#include <iostream>
#include "../variables.h"
#include <iomanip>
#include <algorithm>
#include <numeric>
#include <tuple>

class PotentialsMethod {
public:
  PotentialsMethod() = default;

  void outputResults()
  {
    std::cout << "\n";
    std::cout << "2.2) Метод потенциалов\n";
    const int methodResult = result();
    std::cout << "Общая стоимость плана перевозки:\nZ = " << methodResult << "\n";
  }

private:
  void outputTable(vectorMatrixInt matrix) {      
    std::cout << "-------------------------\n";
    for(int i = 0; i < matrix.size(); i++) {
      std::cout << "| ";
      for(int j = 0; j < matrix[i].size(); j++) {
        std::cout << std::setw(5) << matrix[i][j] << " | ";
      }
      std::cout << "\n";
    }
    std::cout << "-------------------------\n";
  }

  const int result() {
    return 0;
  }
};