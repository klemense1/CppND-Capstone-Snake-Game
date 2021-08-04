#ifndef GEOMETRY_H
#define GEOMETRY_H
#include <iostream>

namespace geometry {

template <typename T> struct Point2d {
  Point2d(T x, T y) : x(x), y(y) {}
  Point2d() : Point2d(0, 0){};
  T x;
  T y;
};

typedef Point2d<int> Point2dInt;
typedef Point2d<float> Point2dFloat;

template <typename T>
std::ostream &operator<<(std::ostream &os, const Point2d<T> &pt) {
  os << pt.x << ", " << pt.y;
}

template <typename T1, typename T2>
bool Collides(const Point2d<T1> &p1, const Point2d<T2> &p2) {
  if (static_cast<int>(p1.x) == static_cast<int>(p2.x) &&
      static_cast<int>(p1.y) == static_cast<int>(p2.y)) {
    return true;
  } else {
    return false;
  }
}

} // namespace geometry

#endif