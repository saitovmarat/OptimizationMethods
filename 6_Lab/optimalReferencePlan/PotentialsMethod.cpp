#include <iostream>
#include "../variables.h"
#include <iomanip>
#include <algorithm>
#include <numeric>
#include <tuple>

class PotentialsMethod {
public:
  PotentialsMethod(const vectorMatrixInt& startingPlan) {
    this->startingPlan = startingPlan;
    setStartingBasis(startingPlan);
  }

  void outputResults()
  {
    std::cout << "\n";
    std::cout << "2.2) Метод потенциалов\n";
    const int methodResult = getMinDeliveryCost();
    std::cout << "Общая стоимость плана перевозки:\nZ = " << methodResult << "\n";
  }

private:
  vectorMatrixInt startingPlan;
  vectorMatrixInt basis = {
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0}
  };

  void setStartingBasis(vectorMatrixInt plan) {
    for (int i = 0; i < plan.size(); i++) {
      for (int j = 0; j < plan[i].size(); j++) {
        if (plan[i][j] != 0) {
          basis[i][j] = 1;
        }
      }
    }
  }
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

  std::vector<std::vector<int>> getPotentials() {
    vectorMatrixInt deliveryCosts = variables::DELIVERY_COSTS;
    std::vector<int> potentialsForProviders = { 0, -1, -1 };
    std::vector<int> potentialsForConsumers = { -1, -1, -1 };

    bool potentialsFilled = false;
    while(!potentialsFilled) {
      for (int row = 0; row < basis.size(); row++) {        // по поставщикам
        for (int col = 0; col < basis[row].size(); col++) { // по потребителям
          if(basis[row][col] == 0) {
            continue;
          }
          if (potentialsForProviders[row] != -1 && 
              potentialsForConsumers[col] == -1)
          {
            potentialsForConsumers[col] = deliveryCosts[row][col] - potentialsForProviders[row];
          }
          else if (potentialsForProviders[row] == -1 && 
                   potentialsForConsumers[col] != -1)
          {
            potentialsForProviders[row] = deliveryCosts[row][col] - potentialsForConsumers[col];
          }
        }
      }
      // Если потенциалы не досчитались, проходимся по матрице ещё раз
      for(int i = 0; i < potentialsForProviders.size(); i++) {
        if(potentialsForProviders[i] == -1) {
          goto nextIteration;
        }
      }
      for(int i = 0; i < potentialsForConsumers.size(); i++) {
        if(potentialsForConsumers[i] == -1) {
          goto nextIteration;
        }
      }
      potentialsFilled = true;
      
      nextIteration:;
    }
    return { potentialsForProviders, potentialsForConsumers }; 
  }

  bool noNegativeEvaluations(vectorMatrixInt evaluations) {
    for (int row = 0; row < evaluations.size(); row++) {
      for (int col = 0; col < evaluations[row].size(); col++) {
        if(evaluations[row][col] < 0) {
          return false;
        }
      }
    }
    return true;
  }
  
  void fillPlusAndMinusElementsIndexesVectors(
    vectorMatrixInt currentPlan,
    int startingRow, int startingCol,
    std::vector<std::pair<int, int>>& plusElementsIndexes,
    std::vector<std::pair<int, int>>& minusElementsIndexes)
  {
    bool cycleIsFinished = false;  
    while (!cycleIsFinished) {
      int currentRow = startingRow;
      int currentCol = startingCol;
      for (int col = startingCol; col < currentPlan[startingRow].size(); col++) {
        if (currentPlan[currentRow][col] != 0) {
          minusElementsIndexes.push_back({ currentRow, col });
          currentCol = col;
          break;
        }
      }
      for (int row = currentRow - 1; row >= 0; row--) {
        if (currentPlan[row][currentCol] != 0) {
          plusElementsIndexes.push_back({ row, currentCol });
          currentRow = row;
          break;
        }
      }
      minusElementsIndexes.push_back({ currentRow, startingCol });
      cycleIsFinished = true;
    }
  }

  int countDeliverySum(vectorMatrixInt currentPlan) {
    vectorMatrixInt deliveryCosts = variables::DELIVERY_COSTS;
    int sum = 0;
    for (int row = 0; row < currentPlan.size(); row++) {
      for (int col = 0; col < currentPlan[row].size(); col++) {
        sum += deliveryCosts[row][col] * currentPlan[row][col];
      }
    }
    return sum;
  }

  const int getMinDeliveryCost() {
    vectorMatrixInt deliveryCosts = variables::DELIVERY_COSTS;
    std::vector<int> stocks = variables::STOCKS;
    std::vector<int> needs = variables::NEEDS;
    vectorMatrixInt currentPlan = startingPlan;

    while (true) {
      outputTable(currentPlan);
      std::vector<std::vector<int>> potentials = getPotentials();
      std::vector<int> potentialsForProviders = potentials[0];
      std::vector<int> potentialsForConsumers = potentials[1];

      // Считаем оценки в не базисных ячейках
      vectorMatrixInt evaluations = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}
      };
      int minEvaluation = std::numeric_limits<int>::max();
      std::pair<int, int> minEvaluationInd = { -1, -1 };
      for (int row = 0; row < currentPlan.size(); row++) {
        for (int col = 0; col < currentPlan[row].size(); col++) {
          if (currentPlan[row][col] != 0) {
            continue;
          }
          int evaluation = deliveryCosts[row][col] - 
            (potentialsForProviders[row] + potentialsForConsumers[col]);

          evaluations[row][col] = evaluation;

          if (evaluation < minEvaluation) {
            minEvaluation = evaluation;
            minEvaluationInd.first = row;
            minEvaluationInd.second = col;
          }
        }
      }

      if (noNegativeEvaluations(evaluations)) {
        return countDeliverySum(currentPlan); 
      }

      int elementToAddToBasisRow = minEvaluationInd.first;
      int elementToAddToBasisСol = minEvaluationInd.second;
      basis[elementToAddToBasisRow][elementToAddToBasisСol] = 1;

      std::vector<std::pair<int, int>> plusElementsIndexes;
      std::vector<std::pair<int, int>> minusElementsIndexes;
      plusElementsIndexes.push_back(minEvaluationInd);

      fillPlusAndMinusElementsIndexesVectors(
        startingPlan,
        minEvaluationInd.first, minEvaluationInd.second,
        plusElementsIndexes, minusElementsIndexes);

      int minElementFromMinuses = std::numeric_limits<int>::max();
      int elementToDeleteFromBasisRow;
      int elementToDeleteFromBasisСol;
      for (int i = 0; i < minusElementsIndexes.size(); i++) {
        int row = minusElementsIndexes[i].first;
        int col = minusElementsIndexes[i].second;
        if (currentPlan[row][col] < minElementFromMinuses) {
          minElementFromMinuses = currentPlan[row][col];
          elementToDeleteFromBasisRow = row;
          elementToDeleteFromBasisСol = col;
        }
      }
      
      basis[elementToDeleteFromBasisRow][elementToDeleteFromBasisСol] = 0;

      for(int i = 0; i < plusElementsIndexes.size(); i++) {
        int row = plusElementsIndexes[i].first;
        int col = plusElementsIndexes[i].second;
        currentPlan[row][col] += minElementFromMinuses;
      }
      for(int i = 0; i < minusElementsIndexes.size(); i++) {
        int row = minusElementsIndexes[i].first;
        int col = minusElementsIndexes[i].second;
        currentPlan[row][col] -= minElementFromMinuses;
      }
    }

    return 0;
  }
};