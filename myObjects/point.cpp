#include <vector>
#include <cmath>
#include "./vector.hpp"

#ifndef POINT_H
#define POINT_H

struct Point
{
  myObjects::Vector<double> coords = {};

  Point() {}
  Point(myObjects::Vector<double> coords) : coords(coords) {}

  Point operator+(const Point& point) const
  {
    myObjects::Vector<double> resultCoords;
    for (size_t i = 0; i < coords.size(); ++i)
    {
      resultCoords.push_back(coords[i] + point.coords[i]);
    }
    return Point(resultCoords);
  }

  Point operator+(const double& num) {
    myObjects::Vector<double> resultCoords;
    for (size_t i = 0; i < coords.size(); ++i)
    {
      resultCoords.push_back(coords[i] + num);
    }
    return Point(resultCoords);
  }

  Point operator-(const Point& point) const
  {
    myObjects::Vector<double> resultCoords;
    for (size_t i = 0; i < coords.size(); ++i)
    {
      resultCoords.push_back(coords[i] - point.coords[i]);
    }
    return Point(resultCoords);
  }

  Point operator-(const double& num) {
    myObjects::Vector<double> resultCoords;
    for (size_t i = 0; i < coords.size(); ++i)
    {
      resultCoords.push_back(coords[i] - num);
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
  return sqrt(sum);
}


#endif // POINT_H