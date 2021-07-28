#ifndef FOOD_H
#define FOOD_H

#include "SDL.h"
#include "geometry.h"
#include "object.h"
#include "param.h"
#include "random_generator.h"
#include "snake.h"
#include <memory>
#include <vector>

class Renderer;

class Food : public Object {};

class Apple : public Food {
public:
  Apple(const Snake &snake, const param::Settings &settings);
  bool CollidesWithSnakeHead(const Snake &snake) const override;
  bool CollidesWithSnake(const Snake &snake) const override;
  bool Update() override;
  void Render(Renderer *renderer) const override;

private:
  geometry::Point2dInt _pt;
  Rand_Int _random_w;
  Rand_Int _random_h;
};

#endif