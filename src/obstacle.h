#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "SDL.h"
#include "geometry.h"
#include "object.h"
#include "param.h"
#include "random_generator.h"
#include "snake.h"
#include <memory>
#include <vector>

class Renderer;

class Obstacle : public Object {
  public:
  
  protected:
    std::vector<geometry::Point2dInt> _pts;
};

class Fence : public Obstacle {
public:
  Fence(const param::Settings &settings);
  bool CollidesWithSnakeHead(const Snake &snake) const override;
  bool CollidesWithSnake(const Snake &snake) const override;
  bool Update() override;
  void Render(Renderer *renderer) const override;

private:
  void GenerateFence();
  // std::vector<geometry::Point2dInt> _pts;
  Rand_Int _random_w;
  Rand_Int _random_h;
};

class BouncingBall : public Obstacle {};

#endif