#ifndef GAME_H
#define GAME_H

#include "controller.h"
#include "food.h"
#include "geometry.h"
#include "obstacle.h"
#include "renderer.h"
#include "snake.h"
#include <memory>

class Game {
public:
  Game(const param::Settings &settings);
  void Run(Controller const &controller, Renderer &renderer);
  bool ReachedGameEnding() const;

  // TODO: do I need all of these getters?
  int GetScore() const;
  int GetSnakeSize() const;
  int GetCntLevel() const;
  int GetMaxLevels() const;
  int GetCntFood() const;
  int GetFoodPerLevel() const;

private:
  std::unique_ptr<Snake> _snake;
  std::shared_ptr<Food> _food;
  std::vector<std::shared_ptr<Obstacle>> _obstacles;

  int _cnt_level;
  int _cnt_food;

  RandomGenerator _random_generator;

  int _score{0}; // TODO: move to initializer list
  param::Settings _settings;

  void InitializeLevel();
  void Update();
  friend std::ostream &operator<<(std::ostream &os, const Game &g);
};

#endif