#include "obstacle/ball.h"

using geometry::Point2dFloat;
using geometry::Point2dInt;
using param::Settings;

Ball::Ball(const Snake &snake, const Settings &settings)
    : _random_w(0, static_cast<int>(settings.kGridHeight - 1)),
      _grid_size(settings.kGridWidth, settings.kGridHeight), _dir_x(0),
      _dir_y(0), _speed(0.05f), _colour(0x3E, 0xB4, 0x89, 0xFF) {
  GenerateBall(snake);
}

bool Ball::Update() {
  _pt.x = _pt.x + _speed * _dir_x;
  _pt.y = _pt.y + _speed * _dir_y;

  if (_pt.x <= 0 || _pt.x >= _grid_size.x) {
    _dir_x *= -1;
  }
  if (_pt.y <= 0 || _pt.y >= _grid_size.y) {
    _dir_y *= -1;
  }
  return true;
}

void Ball::Render(Renderer *renderer) const {
  renderer->DrawRectangle(_pt, _colour);
}

void Ball::GenerateBall(const Snake &snake) {
  while (true) {
    Rand_Int random_dir(-1, 1);
    _dir_x = random_dir();
    _dir_y = random_dir();

    int x = 1;
    int y = _random_w();
    _pt = Point2dFloat(x, y);
    // Check that the location is not occupied by a snake item before
    // placing food.
    if (!CollidesWithSnake(snake) && !(_dir_x == 0 && _dir_y == 0)) {
      return;
    }
  }
}

bool Ball::CollidesWithSnakeHead(const Snake &snake) const {
  auto pt_int = Point2dInt(_pt.x, _pt.y);
  return (snake.CollidingWithHead(pt_int));
}

bool Ball::CollidesWithSnake(const Snake &snake) const {
  auto pt_int = Point2dInt(_pt.x, _pt.y);
  return (snake.CollidingWithSnake(pt_int));
}