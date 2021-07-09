#ifndef SNAKE_H
#define SNAKE_H

#include "geometry.h"
#include <iostream>
#include <vector>

class Snake {
public:
  enum class Direction { kUp, kDown, kLeft, kRight };

  enum GameState { run, end, pause };

  Snake(int grid_width, int grid_height)
      : _grid_width(grid_width), _grid_height(grid_height),
        _head_x(grid_width / 2), _head_y(grid_height / 2) {}

  void Update();

  void GrowBody();
  bool CollidingWithSnake(int x, int y) const;
  bool CollidingWithHead(int x, int y) const;

  Direction direction = Direction::kUp;

  float _speed{0.1f};
  int _size{1};
  bool _alive{true};
  float _head_x; // TODO: let head be first point in body?
  float _head_y;
  std::vector<geometry::Point2dInt> _body;

private:
  void UpdateHead();
  void UpdateBody(geometry::Point2dInt &current_cell,
                  geometry::Point2dInt &prev_cell);

  bool _growing{false};
  int _grid_width;
  int _grid_height;
  friend std::ostream &operator<<(std::ostream &os, const Snake &snake);
};

#endif