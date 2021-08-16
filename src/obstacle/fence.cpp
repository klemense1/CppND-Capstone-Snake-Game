#include "obstacle/fence.h"

using geometry::Point2dInt;
using param::Settings;

Fence::Fence(const Snake &snake, const Settings &settings)
    : _random_w(0, static_cast<int>(settings.kGridWidth - 1)),
      _random_h(0, static_cast<int>(settings.kGridHeight - 1)),
      _colour(0x8C, 0x8C, 0x5C, 0xFF), _num_corners(settings.numCornersFence) {

  while (_pts.size() == 0) {
    GenerateFence();
    if (CollidesWithSnake(snake)) {
      _pts.clear();
    }
    // Prediction
    Snake new_snake = Snake(snake);
    new_snake.Update();
    if (CollidesWithSnakeHead(new_snake)) {
      _pts.clear();
    }
  }
}

bool Fence::Update() { return true; }

void Fence::Render(Renderer *renderer) const {
  for (Point2dInt const &pt : _pts) {
    renderer->DrawRectangle(pt, _colour);
  }
}

void Fence::GenerateFence() {
  int x0 = _random_w();
  int y0 = _random_h();
  std::vector<geometry::Point2dInt> pts;
  for (int i = 0; i < _num_corners; ++i) {
    int x1 = x0;
    int y1 = y0;
    if (i % 2 == 0) {
      x1 = _random_w();
    } else {
      y1 = _random_h();
    }
    // Check that the location is not occupied by a snake item before placing
    // food.
    auto line = InterpolateLine(x0, x1, y0, y1);
    for (auto &p : line) {
      _pts.push_back(p);
    }
    x0 = x1;
    y0 = y1;
  }
}

std::vector<Point2dInt> Fence::InterpolateLine(int x0, int x1, int y0,
                                               int y1) const {
  std::vector<Point2dInt> line;
  int xi = x0;
  int yi = y0;
  int diff_x = std::abs(x1 - x0);
  int diff_y = std::abs(y1 - y0);
  int length = std::max(diff_x, diff_y);
  for (int j = 1; j <= length; ++j) {
    xi = (x1 - x0) == 0 ? x0 : x0 + j * ((x1 - x0) / std::abs(x1 - x0));
    yi = (y1 - y0) == 0 ? y0 : y0 + j * ((y1 - y0) / std::abs(y1 - y0));
    Point2dInt pt{xi, yi};
    line.push_back(pt);
  }
  return line;
}

bool Fence::CollidesWithSnakeHead(const Snake &snake) const {
  for (auto &pt : _pts) {
    if (snake.CollidingWithHead(pt))
      return true;
  }
  return false;
}

bool Fence::CollidesWithSnake(const Snake &snake) const {
  for (auto &pt : _pts) {
    if (snake.CollidingWithSnake(pt))
      return true;
  }
  return false;
}