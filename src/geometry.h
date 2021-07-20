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

template<typename T>
std::ostream &operator<<(std::ostream &os, const Point2d<T> &pt) {
  os << pt.x << ", " << pt.y;
}
} // namespace geometry

#endif