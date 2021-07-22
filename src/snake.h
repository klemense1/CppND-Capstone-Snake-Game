#ifndef SNAKE_H
#define SNAKE_H

#include "geometry.h"
#include <iostream>
#include <vector>

class Renderer;
class Snake {
public:
  enum class Direction { kUp, kDown, kLeft, kRight };

  Snake(int grid_width, int grid_height)
      : _direction(Direction::kUp), _speed(0.1f), _size(1), _alive(true),
        _growing(false), _grid_size(grid_width, grid_height),
        _head(grid_width / 2, grid_height / 2) {}

  void Update();

  void GrowBody();
  bool Alive() const;
  int Size() const;
  bool CollidingWithSnake(int x, int y) const;
  bool CollidingWithHead(int x, int y) const;

  void Render(Renderer *renderer) const;

  Direction _direction;

  float _speed;

private:
  void UpdateHead();
  void UpdateBody(const geometry::Point2dInt &current_cell,
                  const geometry::Point2dInt &prev_cell);
  friend std::ostream &operator<<(std::ostream &os, const Snake &snake);

  int _size;
  bool _alive;
  geometry::Point2dFloat _head;
  std::vector<geometry::Point2dInt> _body;
  bool _growing;
  geometry::Point2dInt _grid_size;
};

#endif