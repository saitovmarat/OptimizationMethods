#ifndef POINT_H
#define POINT_H

struct Point {
  double x1;
  double x2;
  Point operator + (Point point) {
    return Point{x1 + point.x1, x2 + point.x2};
  }
  Point operator - (Point point) {
    return Point{x1 - point.x1, x2 - point.x2};
  }
  Point operator += (Point point) {
    x1 += point.x1;
    x2 += point.x2;
    return *this;
  }
  Point operator /= (double a) {
    x1 /= a;
    x2 /= a;
    return *this;
  }
};

#endif // POINT_H 