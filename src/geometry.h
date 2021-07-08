#ifndef GEOMETRY_H
#define GEOMETRY_H

namespace geometry {
struct Point2dInt {
  Point2dInt(int x, int y) : x(x), y(y) {}
  Point2dInt() : Point2dInt(0, 0){};
  int x;
  int y;
};
} // namespace geometry

#endif