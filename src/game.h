#ifndef GAME_H
#define GAME_H

#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"
#include <memory>
#include <random>

class Game {
public:
  Game(std::size_t grid_width, std::size_t grid_height, std::size_t max_levels,
       std::size_t food_per_level);
  void Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration);
  int GetScore() const;
  int GetSnakeSize() const;
  int GetCntLevel() const;
  int GetMaxLevels() const;
  int GetCntFood() const;
  int GetFoodPerLevel() const;

private:
  std::unique_ptr<Snake> _snake;
  SDL_Point _food;
  int _cnt_level;
  int _max_levels;
  int _cnt_food;
  const int _food_per_level;
  std::vector<SDL_Point> _fence;

  std::random_device _dev;
  std::mt19937 _engine;
  std::uniform_int_distribution<int> _random_w;
  std::uniform_int_distribution<int> _random_h;

  int _score{0};

  void PlaceFood();
  void PlaceFence();
  bool CollidingWithFence();
  void Update();
};

#endif