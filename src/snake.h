#ifndef SNAKE_H
#define SNAKE_H

#include "geometry.h"
#include "param.h"
#include "renderer.h"
#include <iostream>
#include <vector>

class Renderer;
class Snake {
public:
  enum class Direction { kUp, kDown, kLeft, kRight };

  Snake(const param::Settings &settings)
      : _direction(Direction::kUp), _speed(0.1f), _size(1), _alive(true),
        _growing(false), _grid_size(settings.kGridWidth, settings.kGridHeight),
        _head(settings.kGridWidth / 2, settings.kGridHeight / 2),
        _colour_head_alive(0x00, 0x7A, 0xCC, 0xFF),
        _colour_head_dead(0xFF, 0x00, 0x00, 0xFF),
        _colour_body(0xFF, 0xFF, 0xFF, 0xFF) {}

  void Update();

  void GrowBody();
  bool Alive() const;
  int Size() const;
  bool CollidingWithSnake(const geometry::Point2dInt &pt) const;
  bool CollidingWithHead(const geometry::Point2dInt &pt) const;
  geometry::Point2dFloat GetHead() const { return _head; };

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
  Colour _colour_head_alive;
  Colour _colour_head_dead;
  Colour _colour_body;
};

#endif