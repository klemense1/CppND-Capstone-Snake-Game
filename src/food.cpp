#include "food.h"
#include <iostream>

Apple::Apple(RandomGenerator &generator, const Snake &snake,
             const param::Settings &settings)
    : _random_w(0, static_cast<int>(settings.kGridWidth - 1)),
      _random_h(0, static_cast<int>(settings.kGridHeight - 1)) {
  while (true) {
    _pt.x = _random_w(generator._engine);
    _pt.y = _random_h(generator._engine);
    // Check that the location is not occupied by a snake item before
    // placing food.
    if (!CollidesWithSnake(snake)) {
      return;
    }
  }
}

void Apple::Render(SDL_Renderer *_sdl_renderer, SDL_Rect &block) {
  if (_sdl_renderer) {
    SDL_SetRenderDrawColor(_sdl_renderer, 0xFF, 0xCC, 0x00, 0xFF);
    block.x = _pt.x * block.w;
    block.y = _pt.y * block.h;
    SDL_RenderFillRect(_sdl_renderer, &block);
  }
};

bool Apple::CollidesWithSnakeHead(const Snake &snake) const {
  return snake.CollidingWithHead(_pt.x, _pt.y);
}

bool Apple::CollidesWithSnake(const Snake &snake) const {
  return snake.CollidingWithSnake(_pt.x, _pt.y);
}