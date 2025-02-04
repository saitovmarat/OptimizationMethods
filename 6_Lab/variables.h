#ifndef VARIABLES_H
#define VARIABLES_H
#include "../myObjects/point.cpp"

typedef std::vector<std::vector<int>> vectorMatrixInt; 

namespace variables {
  const vectorMatrixInt DELIVERY_COSTS = 
    {{ 4893, 4280, 6213 },
     { 5327, 4296, 6188 },
     { 6006, 5030, 7224 }};
  const std::vector<int> STOCKS = { 1000, 1700, 1600 };
  const std::vector<int> NEEDS = { 1600, 1000, 1700 };
}

#endif // VARIABLES_H