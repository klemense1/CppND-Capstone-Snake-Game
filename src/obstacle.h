#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "SDL.h"
#include "geometry.h"
#include "param.h"
#include "random_generator.h"
#include "snake.h"
#include <memory>
#include <vector>

class Renderer;
class Obstacle {
public:
  virtual bool CollidesWithSnake(const Snake &snake) const = 0;
  virtual bool Update() = 0;
  virtual void Render(Renderer *renderer) const = 0;
};

class Fence : public Obstacle {
public:
  Fence(const param::Settings &settings);
  bool CollidesWithSnakeHead(const Snake &snake) const;
  bool CollidesWithSnake(const Snake &snake) const;
  bool Update() { return true; };
  void Render(Renderer *renderer) const;

private:
  void GenerateFence();
  // TODO: maybe move pts to base class
  std::vector<geometry::Point2dInt> _pts;
  Rand_Int _random_w;
  Rand_Int _random_h;
};

// class BouncingBall : public Obstacle {

// };

#endif