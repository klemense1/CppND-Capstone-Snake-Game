#include "obstacle.h"
#include "renderer.h"

using geometry::Point2dInt;
using param::Settings;

Fence::Fence(const Settings &settings)
    : _random_w(0, static_cast<int>(settings.kGridWidth - 1)),
      _random_h(0, static_cast<int>(settings.kGridHeight - 1)) {

  while (_pts.size() == 0) {
    GenerateFence();
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

bool Fence::Update() { return true; }

void Fence::Render(Renderer *renderer) const {
  for (Point2dInt const &pt : _pts) {
    renderer->DrawRectangle(pt, 0xFF, 0xA0, 0xA0, 0xFF);
  }
}

void Fence::GenerateFence() {
  int x0 = _random_w();
  int y0 = _random_h();
  std::cout << "GenerateFence x=" << x0 << ", y=" << y0 << "\n";
  int x1, y1;
  std::vector<geometry::Point2dInt> pts;
  // TODO: should become more difficult with each level
  for (int i = 0; i < 2; ++i) {
    if (i % 2 == 0) {
      x1 = _random_w();
      y1 = y0;
    } else {
      x1 = x0;
      y1 = _random_h();
    }
    std::cout << "GenerateFence x=" << x1 << ", y=" << y1 << "\n";
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