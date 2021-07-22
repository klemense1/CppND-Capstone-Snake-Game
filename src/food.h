#ifndef FOOD_H
#define FOOD_H

#include "SDL.h"
#include "geometry.h"
#include "param.h"
#include "random_generator.h"
#include "snake.h"
#include <memory>
#include <vector>

class Renderer;

class Food {
public:
  virtual bool CollidesWithSnakeHead(const Snake &snake) const = 0;
  virtual bool Update() = 0;
  virtual void Render(Renderer *renderer) = 0;

private:
};

class Apple : public Food {
public:
  Apple(const Snake &snake, const param::Settings &settings);
  bool CollidesWithSnakeHead(const Snake &snake) const;
  bool CollidesWithSnake(const Snake &snake) const;
  bool Update() { return true; };
  void Render(Renderer *renderer);

private:
  geometry::Point2dInt _pt;
  Rand_Int _random_w;
  Rand_Int _random_h;
};

#endif