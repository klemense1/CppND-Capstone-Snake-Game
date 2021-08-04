#ifndef GAME_H
#define GAME_H

#include "controller.h"
#include "food/food.h"
#include "geometry.h"
#include "obstacle/obstacle.h"
#include "renderer.h"
#include "snake.h"
#include <memory>

class Game {
public:
  Game(const param::Settings &settings);
  void Run(Controller const &controller, Renderer &renderer);
  bool ReachedGameEnding() const;

private:
  std::unique_ptr<Snake> _snake;
  std::shared_ptr<Food> _food;
  std::vector<std::shared_ptr<Obstacle>> _obstacles;
  int _cnt_level;
  int _cnt_food;
  int _score;
  param::Settings _settings;

  void InitializeLevel();
  void Update();
  friend std::ostream &operator<<(std::ostream &os, const Game &g);
};

#endif