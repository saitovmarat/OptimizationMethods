#include <iostream>
#include "../variables.h"
#include <iomanip>
#include <algorithm>
#include <numeric>
#include <tuple>

typedef std::vector<std::vector<int>> vectorMatrixInt; 

class HungarianMethod {
public:
  HungarianMethod() = default;

  void outputResults()
  {
    std::cout << "\n";
    std::cout << "2.1) Венгерский метод\n";
    const int methodResult = getMinDeliveryCost();
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

  int getDeliveryCost(vectorMatrixInt matrix) {
    int result = 0;
    vectorMatrixInt deliveryCosts = variables::DELIVERY_COSTS;
    for(int row = 0; row < matrix.size(); row++) {
      for(int col = 0; col < matrix[row].size(); col++) {
        result += deliveryCosts[row][col] * matrix[row][col];
      }
    }
    return result;
  }

  vectorMatrixInt getInitialPlan(vectorMatrixInt C) {
    vectorMatrixInt currentPlan = {
      {0, 0, 0},
      {0, 0, 0},
      {0, 0, 0}
    };
    std::vector<int> stocks = variables::STOCKS;
    std::vector<int> needs = variables::NEEDS;
    
    // Построение начального опорного плана
    for (int i = 0; i < C.size(); i++) {
      for (int j = 0; j < C[i].size(); j++) {
        if (C[i][j] != 0) {
          continue;
        }
        int quantity = std::min(stocks[i], needs[j]);
        currentPlan[i][j] = quantity;
        stocks[i] -= quantity;
        needs[j] -= quantity;
        if (stocks[i] == 0) { 
          goto nextIteration;
        }
      }
      nextIteration:;
    }
    return currentPlan;
  }

  vectorMatrixInt getPreprocessedMatrix(vectorMatrixInt matrix) {
    vectorMatrixInt preprocessedMatrix = matrix;
    // Вычитаем минимальный элемент каждого столбца из его элементов
    for (int col = 0; col < preprocessedMatrix[0].size(); col++) {
      int min_in_col = matrix[0][col];
      for (int row = 1; row < col; row++) {
        min_in_col = std::min(min_in_col, matrix[row][col]);
      }
      for (int row = 0; row < preprocessedMatrix.size(); row++) {
        preprocessedMatrix[row][col] -= min_in_col;
      }
    }
    // Вычитаем минимальный элемент каждого ряда из его элементов
    for (int i = 0; i < preprocessedMatrix.size(); i++) {
      int min_in_row = *std::min_element(
        preprocessedMatrix[i].begin(), 
        preprocessedMatrix[i].end()
      );
      for (int j = 0; j < preprocessedMatrix[i].size(); j++) {
        preprocessedMatrix[i][j] -= min_in_row;
      }
    }
    return preprocessedMatrix;
  }

  int getMinFromOuterZone(const vectorMatrixInt& matrix, const std::vector<int>& selectedRows, const std::vector<int>& selectedCols) {
    int minFromOuterZone = std::numeric_limits<int>::max();
    for (int row = 0; row < matrix.size(); row++) {
      if (selectedRows[row] == 1) {
        continue;
      }
      for (int col = 0; col < matrix[row].size(); col++) {
        if (selectedCols[col] == 1) {
          continue;
        }
        minFromOuterZone = std::min(minFromOuterZone, matrix[row][col]);
      }
    }
    return minFromOuterZone;
  }

  const int getMinDeliveryCost() {
    vectorMatrixInt deliveryCosts = variables::DELIVERY_COSTS;
    std::vector<int> stocks = variables::STOCKS;
    std::vector<int> needs = variables::NEEDS;
    vectorMatrixInt C = getPreprocessedMatrix(deliveryCosts);
    vectorMatrixInt currentPlan = getInitialPlan(C);

    while(true) {
      outputTable(currentPlan);
      std::vector<int> stocksRemainders = stocks;
      std::vector<int> needsRemainders = needs;
      for (int i = 0; i < C.size(); i++) {
        for (int j = 0; j < C[i].size(); j++) {
          if (currentPlan[i][j] == 0) {
            continue;
          } 
          stocksRemainders[i] -= currentPlan[i][j];
          needsRemainders[j] -= currentPlan[i][j];
        }
      }
      int sumOfRemainders = 
        std::accumulate(stocksRemainders.begin(), stocksRemainders.end(), 0) + 
        std::accumulate(needsRemainders.begin(), needsRemainders.end(), 0);
      if (sumOfRemainders == 0) {
        return getDeliveryCost(currentPlan);
      }

// Первый этап
      std::vector<std::tuple<int, int>> selectedZerosIndexes;
      for (int row = 0; row < currentPlan.size(); row++) {
        for (int col = 0; col < currentPlan[row].size(); col++) {
          if (currentPlan[row][col] != 0 && C[row][col] == 0) {
            selectedZerosIndexes.push_back({row, col});
          }
        }
      }

      std::vector<int> selectedColumns = { 0, 0, 0 };
      for (int i = 0; i < needsRemainders.size(); i++) {
        if (needsRemainders[i] == 0) {
          selectedColumns[i] = 1;
        }
      }

// Второй этап
      std::vector<int> selectedRows = { 0, 0, 0 };
      std::vector<std::pair<int, int>> markedZerosIndexes;
      for (int cols = 0; cols < C[0].size(); cols++) {
        if(selectedColumns[cols] == 1) {
          continue;
        }
        for (int rows = 0; rows < C.size(); rows++) {
          if(C[rows][cols] == 0) {
            selectedRows[rows] = 1;
            markedZerosIndexes.push_back({rows, cols});
          }
        }
      }

      bool isChainFinished = false;
      std::vector<std::pair<int, int>> chain;

      for (auto& markedZeroIndex : markedZerosIndexes) {
        chain.clear();

        std::pair<int, int> currentChainIndex = markedZeroIndex;
        int currentElementRow = currentChainIndex.first;
        int currentElementCol = currentChainIndex.second;
        chain.push_back({ currentElementRow, currentElementCol });

        if (stocksRemainders[currentElementRow] != 0) {
          isChainFinished = true;
          break;
        }
      }

      if (isChainFinished) {
        int staredMinInChain = std::numeric_limits<int>::max();
        for (int i = 1; i < chain.size(); i += 2) {
          int row = chain[i].first;
          int col = chain[i].second;
          if (currentPlan[row][col] < staredMinInChain) {
            staredMinInChain = currentPlan[row][col];
          }
        }
        int streakedMinInChain = std::min(
          needsRemainders[chain[0].second],
          stocksRemainders[chain[chain.size() - 1].first]
        );
        int teta = std::min(staredMinInChain, streakedMinInChain);
        for (int i = 0; i < chain.size(); i += 2) {
          int row = chain[i].first;
          int col = chain[i].second;
          // Изменяем опорный план
          currentPlan[row][col] += teta;
        }
      }
      else {
//Третий этап
        int minFromOuterZone = getMinFromOuterZone(C, selectedRows, selectedColumns);
        // Отнимаем минимальный элемент из выделенных столбцов
        for (int row = 0; row < C.size(); row++) {
          if (selectedRows[row] == 1) {
            continue;
          }
          for (int col = 0; col < C[row].size(); col++) { 
            C[row][col] -= minFromOuterZone;
          }
        }
        // Добавляем минимальный элемент к выделенным рядам
        for (int col = 0; col < C[0].size(); col++) {
          if (selectedColumns[col] == 0) {
            continue;
          }
          int minInCol = std::numeric_limits<int>::max();
          for (int k = 0; k < C.size(); k++) {
            if (C[k][col] < minInCol) {
              minInCol = C[k][col];
            }
          }
          for (int row = 0; row < C.size(); row++) {
            C[row][col] += abs(minInCol);
          }
        }
      }
    }
  }
};