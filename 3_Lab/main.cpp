#include <iostream>
#include <math.h>
#include "./methods/BarrierFunctionsMethod.cpp"
#include "./methods/PenaltyFunctionsMethod.cpp"


double func(double x1, double x2) {
  return pow(x1, 2) + pow(x2, 2) - 6*x1 - 3*x2 + 5;
}

std::vector<double> D(double x1, double x2) {
  return { x1 + x2 - 3, 2*x1 + x2 - 4 }; 
} 

int main() {
  BarrierFunctionsMethod(func).outputResults();
  PenaltyFunctionsMethod(func).outputResults();
  return 0;
}