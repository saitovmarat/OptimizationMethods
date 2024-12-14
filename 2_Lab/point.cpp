#include <vector>
#ifndef POINT_H
#define POINT_H

struct Point
{
  std::vector<double> coords = {};
  Point() {}
  Point(std::vector<double> coords) : coords(coords) {}

  Point operator+(const Point& point) const
  {
    std::vector<double> resultCoords;
    for (size_t i = 0; i < coords.size(); ++i)
    {
      resultCoords.push_back(coords[i] + point.coords[i]);
    }
    return Point(resultCoords);
  }

  Point operator-(const Point& point) const
  {
    std::vector<double> resultCoords;
    for (size_t i = 0; i < coords.size(); ++i)
    {
      resultCoords.push_back(coords[i] - point.coords[i]);
    }
    return Point(resultCoords);
  }

  Point& operator+=(const Point& point)
  {
    for (size_t i = 0; i < coords.size(); ++i)
    {
      coords[i] += point.coords[i];
    }
    return *this;
  }

  Point& operator-=(const Point& point)
  {
    for (size_t i = 0; i < coords.size(); ++i)
    {
      coords[i] -= point.coords[i];
    }
    return *this;
  }

  Point& operator/=(double a)
  {
    for (size_t i = 0; i < coords.size(); ++i)
    {
      coords[i] /= a;
    }
    return *this;
  }

  bool operator==(const Point& point) const
  {
    for (size_t i = 0; i < coords.size(); ++i)
    {
      if (coords[i] != point.coords[i])
        return false;
    }
    return true;
  }

  bool operator!=(const Point& point) const
  {
    return !(*this == point);
  }
};

/// @return Евклидова норма точки
double getNorm(const Point& point)
{
  double sum{0.0};
  for (const auto& coord : point.coords)
  {
    sum += coord * coord;
  }
  return std::sqrt(sum);
}


#endif // POINT_H