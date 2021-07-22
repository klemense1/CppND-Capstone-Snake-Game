#ifndef RENDERER_H
#define RENDERER_H

#include "SDL.h"
#include "food.h"
#include "geometry.h"
#include "obstacle.h"
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
  void DrawRectangle(const geometry::Point2dInt, Uint8 r, Uint8 g, Uint8 b,
                     Uint8 a);
  void UpdateWindowTitle(int score, int cnt_level, int max_levels, int cnt_food,
                         int food_per_level, int fps);

private:
  SDL_Window *_sdl_window; // TODO: let renderer not own those ?
  SDL_Renderer *_sdl_renderer;
  SDL_Rect _block;

  const std::size_t _screen_width;
  const std::size_t _screen_height;
  const std::size_t _grid_width;
  const std::size_t _grid_height;
};

#endif