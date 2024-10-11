#include <iostream>
#include <iomanip>
#include <math.h>
#include <map>
#include "point.cpp"
#include "methods/Hook-JeevesMethod.cpp"

Point STARTPOINT = {0, 0};
Point DELTAX = { 2, 2 };
#define ALPHA 2
#define EPS 0.1

double func(Point point) {
  return 2 * pow((point.x1 - 1), 2) + pow((point.x2 - 6), 2);
}
 
int main() 
{
  HookJeevesMethod(STARTPOINT, DELTAX, ALPHA, EPS, func).outputResults();
}