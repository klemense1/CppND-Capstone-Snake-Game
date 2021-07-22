#include "food.h"
#include "renderer.h"
#include <iostream>

Apple::Apple(const Snake &snake, const param::Settings &settings)
    : _random_w(0, static_cast<int>(settings.kGridWidth - 1)),
      _random_h(0, static_cast<int>(settings.kGridHeight - 1)) {
  while (true) {
    _pt.x = _random_w();
    _pt.y = _random_h();
      std::cout << "GenerateApple x=" << _pt.x << ", y=" << _pt.y << "\n";
    // Check that the location is not occupied by a snake item before
    // placing food.
    if (!CollidesWithSnake(snake)) {
      return;
    }
  }
}

void Apple::Render(Renderer *renderer) {
  if (renderer) {
    renderer->DrawRectangle(_pt, 0xFF, 0xCC, 0x00, 0xFF);
  }
};

bool Apple::CollidesWithSnakeHead(const Snake &snake) const {
  return snake.CollidingWithHead(_pt.x, _pt.y);
}

bool Apple::CollidesWithSnake(const Snake &snake) const {
  return snake.CollidingWithSnake(_pt.x, _pt.y);
}