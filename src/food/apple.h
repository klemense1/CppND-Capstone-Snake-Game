#ifndef APPLE_H
#define APPLE_H

#include "SDL.h"
#include "food.h"
#include "geometry.h"
#include "param.h"
#include "random_generator.h"
#include "renderer.h"
#include "snake.h"
#include <memory>
#include <vector>

class Apple : public Food {
public:
  Apple(const Snake &snake, const param::Settings &settings);
  bool CollidesWithSnakeHead(const Snake &snake) const override;
  bool CollidesWithSnake(const Snake &snake) const override;
  bool Update() override;
  void Render(Renderer *renderer) const override;
  geometry::Point2dInt GetPosition() const { return _pt; }

private:
  geometry::Point2dInt _pt;
  Rand_Int _random_w;
  Rand_Int _random_h;
  Colour _colour;
};

#endif