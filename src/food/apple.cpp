#include "food/apple.h"
#include <iostream>

Apple::Apple(const Snake &snake, const param::Settings &settings)
    : _random_w(0, static_cast<int>(settings.kGridWidth - 1)),
      _random_h(0, static_cast<int>(settings.kGridHeight - 1)),
      _colour(0xFF, 0xCC, 0x00, 0xFF) {
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

bool Apple::CollidesWithSnakeHead(const Snake &snake) const {
  return snake.CollidingWithHead(_pt);
}

bool Apple::CollidesWithSnake(const Snake &snake) const {
  return snake.CollidingWithSnake(_pt);
}

bool Apple::Update() { return true; };

void Apple::Render(Renderer *renderer) const {
  if (renderer) {
    renderer->DrawRectangle(_pt, _colour);
  }
};
