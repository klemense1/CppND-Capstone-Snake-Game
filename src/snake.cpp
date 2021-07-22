#include "snake.h"
#include "renderer.h"
#include <cmath>
#include <iostream>

using geometry::Point2dInt;

void Snake::Update() {
  // We first capture the head's cell before updating.
  Point2dInt prev_cell{static_cast<int>(_head.x), static_cast<int>(_head.y)};
  UpdateHead();
  // Capture the head's cell after updating.
  Point2dInt current_cell{static_cast<int>(_head.x), static_cast<int>(_head.y)};

  // Update all of the body vector items if the snake head has moved to a new
  // cell.
  if (current_cell.x != prev_cell.x || current_cell.y != prev_cell.y) {
    UpdateBody(current_cell, prev_cell);
  }
}

void Snake::UpdateHead() {
  switch (_direction) {
  case Direction::kUp:
    _head.y -= _speed;
    break;

  case Direction::kDown:
    _head.y += _speed;
    break;

  case Direction::kLeft:
    _head.x -= _speed;
    break;

  case Direction::kRight:
    _head.x += _speed;
    break;
  }

  // Wrap the Snake around to the beginning if going off of the screen.
  _head.x = fmod(_head.x + _grid_size.x, _grid_size.x);
  _head.y = fmod(_head.y + _grid_size.y, _grid_size.y);
}

void Snake::UpdateBody(const Point2dInt &current_head_cell,
                       const Point2dInt &prev_head_cell) {
  // Add previous head location to vector
  _body.push_back(prev_head_cell);

  if (!_growing) {
    // Remove the tail from the vector.
    _body.erase(_body.begin());
  } else {
    _growing = false;
    _size++;
  }

  // Check if the snake has died.
  for (auto const &item : _body) {
    if (current_head_cell.x == item.x && current_head_cell.y == item.y) {
      _alive = false;
    }
  }
}

void Snake::GrowBody() { _growing = true; }

bool Snake::Alive() const { return _alive; }

int Snake::Size() const { return _size; }

void Snake::Render(Renderer *renderer) const {
  if (renderer) {
    // Render snake's body
    for (auto const &pt : _body) {
      renderer->DrawRectangle(pt, 0xFF, 0xFF, 0xFF, 0xFF);
    }
    // Render snake's head
    Point2dInt pt = Point2dInt(_head.x, _head.y);
    if (_alive) {
      renderer->DrawRectangle(pt, 0x00, 0x7A, 0xCC, 0xFF);
    } else {
      renderer->DrawRectangle(pt, 0xFF, 0x00, 0x00, 0xFF);
    }
  }
};

// Inefficient method to check if cell is occupied by snake.
bool Snake::CollidingWithSnake(int x, int y) const {
  if (CollidingWithHead(x, y)) {
    std::cout << "Colliding with head\n";
    return true;
  }
  for (auto const &item : _body) {
    if (x == item.x && y == item.y) {
      std::cout << "Colliding with body\n";
      return true;
    }
  }
  return false;
}

bool Snake::CollidingWithHead(int x, int y) const {
  if (x == static_cast<int>(_head.x) && y == static_cast<int>(_head.y)) {
    return true;
  } else {
    return false;
  }
}

std::ostream &operator<<(std::ostream &os, const Snake &snake) {
  os << "Snake with body length " << snake._body.size() << " and head at ("
     << snake._head << ")";
}