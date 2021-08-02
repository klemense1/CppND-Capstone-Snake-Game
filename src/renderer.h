#ifndef RENDERER_H
#define RENDERER_H

#include "SDL.h"
#include "food.h"
#include "geometry.h"
#include "obstacle/obstacle.h"
#include "param.h"
#include "snake.h"
#include <memory>
#include <vector>

class Renderer {
public:
  Renderer(const param::Settings &settings);
  ~Renderer();

  void Render(Snake const &snake, std::shared_ptr<Food> const &food,
              std::vector<std::shared_ptr<Obstacle>> const &obstacles);

  void UpdateWindowTitle(int score, int cnt_level, int max_levels, int cnt_food,
                         int food_per_level, int fps);

  template <typename T>
  void DrawRectangle(const geometry::Point2d<T> point, Uint8 r, Uint8 g,
                     Uint8 b, Uint8 a) {
    SDL_SetRenderDrawColor(_sdl_renderer, r, g, b, a);
    SDL_Rect block;
    block.w = _screen_width / _grid_width;
    block.h = _screen_height / _grid_height;
    block.x = static_cast<int>(point.x * block.w);
    block.y = static_cast<int>(point.y * block.h);
    SDL_RenderFillRect(_sdl_renderer, &block);
  }

private:
  SDL_Window *_sdl_window;
  SDL_Renderer *_sdl_renderer;
  SDL_Rect _block;

  const std::size_t _screen_width;
  const std::size_t _screen_height;
  const std::size_t _grid_width;
  const std::size_t _grid_height;
};

#endif