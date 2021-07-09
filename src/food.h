#ifndef FOOD_H
#define FOOD_H

#include "SDL.h"
#include "geometry.h"
#include "param.h"
#include "random_generator.h"
#include "snake.h"
#include <memory>
#include <vector>

class Food {
public:
  virtual bool CollidesWithSnakeHead(const Snake &snake) const = 0;
  virtual bool Update() = 0;
  virtual void Render(SDL_Renderer *_sdl_renderer, SDL_Rect &sdl_block) = 0;

private:
};

class Apple : public Food {
public:
  Apple(RandomGenerator &generator, const Snake &snake,
        const param::Settings &settings);
  bool CollidesWithSnakeHead(const Snake &snake) const;
  bool CollidesWithSnake(const Snake &snake) const;
  bool Update() { return true; };
  void Render(SDL_Renderer *_sdl_renderer, SDL_Rect &sdl_block);

private:
  geometry::Point2dInt _pt;
  std::uniform_int_distribution<int> _random_w;
  std::uniform_int_distribution<int> _random_h;
};

#endif