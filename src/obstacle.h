#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "SDL.h"
#include "geometry.h"
#include "param.h"
#include "random_generator.h"
#include "snake.h"
#include <memory>
#include <vector>

class Obstacle {
public:
  virtual bool CollidesWithSnake(const Snake &snake) const = 0;
  virtual bool Update() = 0;
  virtual void Render(SDL_Renderer *_sdl_renderer, SDL_Rect &block) const = 0;
};

class Fence : public Obstacle {
public:
  Fence(RandomGenerator &generator, const param::Settings &settings);
  bool CollidesWithSnakeHead(const Snake &snake) const;
  bool CollidesWithSnake(const Snake &snake) const;
  bool Update() { return true; };
  void Render(SDL_Renderer *_sdl_renderer, SDL_Rect &block) const;

private:
  // TODO: maybe move pts to base class
  std::vector<geometry::Point2dInt> _pts;
  std::uniform_int_distribution<int> _random_w;
  std::uniform_int_distribution<int> _random_h;
};

// class BouncingBall : public Obstacle {

// };

#endif