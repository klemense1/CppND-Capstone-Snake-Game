#include "obstacle.h"
#include "renderer.h"

using geometry::Point2dInt;
using param::Settings;

Fence::Fence(RandomGenerator &generator, const Settings &settings)
    : _pts(), _random_w(0, static_cast<int>(settings.kGridWidth - 1)),
      _random_h(0, static_cast<int>(settings.kGridHeight - 1)) {
  int x0 = _random_w(generator._engine);
  int y0 = _random_h(generator._engine);
  int x1, y1;

  // TODO: should become more dificult with each level
  for (int i = 0; i < 2; ++i) {
    if (i % 2 == 0) {
      x1 = _random_w(generator._engine);
      y1 = y0;
    } else {
      x1 = x0;
      y1 = _random_h(generator._engine);
    }
    // Check that the location is not occupied by a snake item before placing
    // food.
    for (int j = 0; j < std::max(x1 - x0, y1 - y0); ++j) {
      Point2dInt pt;
      pt.x = x0 + j / std::max(1, (x1 - x0));
      pt.y = y0 + j / std::max(1, (y1 - y0));
      _pts.push_back(pt);
    }
  }
}

void Fence::Render(Renderer *renderer) const {
  for (Point2dInt const &pt : _pts) {
    renderer->DrawRectangle(pt, 0xFF, 0xA0, 0xA0, 0xFF);
  }
}

bool Fence::CollidesWithSnakeHead(const Snake &snake) const {
  for (auto &pt : _pts) {
    if (snake.CollidingWithHead(pt.x, pt.y))
      return true;
  }
  return false;
}

bool Fence::CollidesWithSnake(const Snake &snake) const {
  for (auto &pt : _pts) {
    if (snake.CollidingWithSnake(pt.x, pt.y))
      return true;
  }
  return false;
}