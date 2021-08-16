#ifndef OBSTACLE_FENCE_H
#define OBSTACLE_FENCE_H

#include "geometry.h"
#include "obstacle/obstacle.h"
#include "param.h"
#include "random_generator.h"
#include "renderer.h"
#include "snake.h"

typedef std::vector<geometry::Point2dInt> Line2dInt;
class Fence : public Obstacle {
public:
  Fence(const Snake &snake, const param::Settings &settings);
  bool Update() override;
  void Render(Renderer *renderer) const override;
  bool CollidesWithSnakeHead(const Snake &snake) const override;
  bool CollidesWithSnake(const Snake &snake) const override;
  Line2dInt GetPoints() const { return _pts; }

private:
  void GenerateFence();
  Line2dInt InterpolateLine(int x0, int x1, int y0,
                                                    int y1) const;
  Line2dInt _pts;
  Rand_Int _random_w;
  Rand_Int _random_h;
  Colour _colour;
  int _num_corners;
};

#endif