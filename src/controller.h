#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "snake.h"
#include <map>

enum class GameState { running, ending, paused };
class Controller {
public:
  void HandleInput(GameState &state, Snake *snake) const;

private:
  void ChangeDirection(Snake *snake, Snake::Direction input) const;

  typedef std::map<Snake::Direction, Snake::Direction> OIMap;
  static OIMap _oppositeInputMapping;
};

#endif