#include <math.h>
#include "point.cpp"
#include "methods/Hook-JeevesMethod.cpp"

// Hook-Jeeves, Newton

Point START_POINT = {0, 0};
Point DELTAX = { 2, 2 };
#define ALPHA 2
#define EPS 0.1

double func(Point point) {
  return 2 * pow((point.x1 - 1), 2) + pow((point.x2 - 6), 2);
}
 
int main() {
  HookJeevesMethod(START_POINT, DELTAX, ALPHA, EPS, func).outputResults();
  
  return 0;
}