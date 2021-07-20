#ifndef SNAKE_H
#define SNAKE_H

#include "geometry.h"
#include <iostream>
#include <vector>

class Renderer;
class Snake {
public:
  enum class Direction { kUp, kDown, kLeft, kRight };

  enum GameState { run, end, pause };

  Snake(int grid_width, int grid_height)
      : _grid_size(grid_width, grid_height),
        _head(grid_width / 2, grid_height / 2) {}

  void Update();

  void GrowBody();
  bool CollidingWithSnake(int x, int y) const;
  bool CollidingWithHead(int x, int y) const;

  void Render(Renderer *renderer) const;

  Direction direction = Direction::kUp;

  float _speed{0.1f};
  int _size{1};
  bool _alive{true};
  geometry::Point2dFloat _head;
  std::vector<geometry::Point2dInt> _body;

private:
  void UpdateHead();
  void UpdateBody(geometry::Point2dInt &current_cell,
                  geometry::Point2dInt &prev_cell);

  bool _growing{false};
  geometry::Point2dInt _grid_size;
  friend std::ostream &operator<<(std::ostream &os, const Snake &snake);
};

#endif