#include <iostream>
#include "../variables.h"
#include <iomanip>
#include <algorithm>
#include <numeric>
#include <tuple>

class HungarianMethod {
public:
  HungarianMethod() = default;

  void outputResults()
  {
    std::cout << "\n";
    std::cout << "2.1) Венгерский метод\n";
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

  int getResult(vectorMatrixInt matrix) {
    int result = 0;
    vectorMatrixInt deliveryCosts = variables::DELIVERY_COSTS;
    for(int row = 0; row < matrix.size(); row++) {
      for(int col = 0; col < matrix[row].size(); col++) {
        result += deliveryCosts[row][col] * matrix[row][col];
      }
    }
    return result;
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

  const int result() {
    vectorMatrixInt deliveryCosts = variables::DELIVERY_COSTS;
    std::vector<int> stocks = variables::STOCKS;
    std::vector<int> needs = variables::NEEDS;
    vectorMatrixInt C = getPreprocessedMatrix(deliveryCosts);
    
    while(true) {
      vectorMatrixInt currentPlan = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}
      };
      std::vector<int> stocksRemainders = stocks;
      std::vector<int> needsRemainders = needs;
      
      int firstValidColumnInd = 0;
      // Заполнение матрицы X
      for (int i = 0; i < C.size(); i++) {
        for (int j = 0; j < C[i].size(); j++) {
          if (C[i][j] != 0) {
            continue;
          }
          int quantity = std::min(needsRemainders[j], stocksRemainders[i]);
          currentPlan[i][j] = quantity;
          stocksRemainders[i] -= quantity;
          needsRemainders[j] -= quantity;
          if (stocksRemainders[i] == 0) { 
            goto nextIteration;
          }
        }
        nextIteration:;
      }
      outputTable(currentPlan);
      
      // Получаем сумму остатков и если она равна нулю - выхоим из метода
      int sumOfRemainders = 
        std::accumulate(stocksRemainders.begin(), stocksRemainders.end(), 0) + 
        std::accumulate(needsRemainders.begin(), needsRemainders.end(), 0);
      if (sumOfRemainders == 0) {
        return getResult(currentPlan);
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
      std::vector<std::tuple<int, int>> markedZerosIndexes;
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
      std::tuple<int, int> startChainIndex;
      std::tuple<int, int> endChainIndex;
      for(auto& markedZeroIndex : markedZerosIndexes) {
        startChainIndex = markedZeroIndex;
        std::tuple<int, int> currentChainIndex = startChainIndex;

        int rowInd = std::get<0>(markedZeroIndex);
        if(stocksRemainders[rowInd] != 0) {
          isChainFinished = true;
          endChainIndex = currentChainIndex;
          break;
        }
      }
      // TODO: Также нужно сравнивать с 0* элементами матрицы X
      if(isChainFinished) {
        int startChainCol = std::get<1>(startChainIndex);
        int endChainRow = std::get<0>(endChainIndex);
        int teta = std::min(
          stocksRemainders[endChainRow], 
          needsRemainders[startChainCol]
        );
        for(auto& markedZeroIndex : markedZerosIndexes) {
          int row = std::get<0>(markedZeroIndex);
          int col = std::get<1>(markedZeroIndex);
          currentPlan[row][col] += teta;
        }
      }
      else {
//Третий этап
        int minFromOuterZone = getMinFromOuterZone(C, selectedRows, selectedColumns);
        // Отнимаем минимальный элемент из выделенных столбцов
        for(int row = 0; row < C.size(); row++) {
          if(selectedRows[row] == 1) {
            continue;
          }
          for(int col = 0; col < C[row].size(); col++) { 
            C[row][col] -= minFromOuterZone;
          }
        }
        // Добавляем минимальный элемент к выделенным рядам
        for(int col = 0; col < C[0].size(); col++) {
          if(selectedColumns[col] == 0) {
            continue;
          }
          int minInCol = std::numeric_limits<int>::max();
          for(int k = 0; k < C.size(); k++) {
            if(C[k][col] < minInCol) {
              minInCol = C[k][col];
            }
          }
          for(int row = 0; row < C.size(); row++) {
            C[row][col] += abs(minInCol);
          }
        }
      }
    }
  }
};