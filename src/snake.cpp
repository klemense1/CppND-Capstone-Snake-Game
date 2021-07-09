#include "snake.h"
#include "renderer.h"
#include <cmath>
#include <iostream>

using geometry::Point2dInt;

void Snake::Update() {
  Point2dInt prev_cell{
      static_cast<int>(_head_x),
      static_cast<int>(
          _head_y)}; // We first capture the head's cell before updating.
  UpdateHead();
  Point2dInt current_cell{
      static_cast<int>(_head_x),
      static_cast<int>(_head_y)}; // Capture the head's cell after updating.

  // Update all of the body vector items if the snake head has moved to a new
  // cell.
  if (current_cell.x != prev_cell.x || current_cell.y != prev_cell.y) {
    UpdateBody(current_cell, prev_cell);
  }
}

void Snake::UpdateHead() {
  switch (direction) {
  case Direction::kUp:
    _head_y -= _speed;
    break;

  case Direction::kDown:
    _head_y += _speed;
    break;

  case Direction::kLeft:
    _head_x -= _speed;
    break;

  case Direction::kRight:
    _head_x += _speed;
    break;
  }

  // Wrap the Snake around to the beginning if going off of the screen.
  _head_x = fmod(_head_x + _grid_width, _grid_width);
  _head_y = fmod(_head_y + _grid_height, _grid_height);
}

void Snake::UpdateBody(Point2dInt &current_head_cell,
                       Point2dInt &prev_head_cell) {
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

void Snake::Render(Renderer *renderer) const {
  if (renderer) {
    // Render snake's body
    for (auto const &pt : _body) {
      renderer->DrawRectangle(pt, 0xFF, 0xFF, 0xFF, 0xFF);
    }
    // Render snake's head
    Point2dInt pt = Point2dInt(_head_x, _head_y);
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
  if (x == static_cast<int>(_head_x) && y == static_cast<int>(_head_y)) {
    return true;
  } else {
    return false;
  }
}

std::ostream &operator<<(std::ostream &os, const Snake &snake) {
  os << "Snake with body length " << snake._body.size() << " and head at ("
     << snake._head_x << ", " << snake._head_y << ")";
}