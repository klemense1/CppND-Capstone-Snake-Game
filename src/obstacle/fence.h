#ifndef OBSTACLE_FENCE_H
#define OBSTACLE_FENCE_H

#include "geometry.h"
#include "obstacle/obstacle.h"
#include "param.h"
#include "random_generator.h"
#include "snake.h"

class Fence : public Obstacle {
public:
  Fence(const param::Settings &settings);
  bool Update() override;
  void Render(Renderer *renderer) const override;
  bool CollidesWithSnakeHead(const Snake &snake) const override;
  bool CollidesWithSnake(const Snake &snake) const override;

private:
  void GenerateFence();
  std::vector<geometry::Point2dInt> _pts;
  Rand_Int _random_w;
  Rand_Int _random_h;
};

#endif