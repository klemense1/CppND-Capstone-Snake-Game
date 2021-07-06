#ifndef RENDERER_H
#define RENDERER_H

#include "SDL.h"
#include "snake.h"
#include <memory>
#include <vector>

class Renderer {
public:
  Renderer(const std::size_t _screen_width, const std::size_t _screen_height,
           const std::size_t grid_width, const std::size_t grid_height);
  ~Renderer();

  void Render(std::unique_ptr<Snake> const &snake, SDL_Point const &food,
              std::vector<SDL_Point> const &fence);
  void UpdateWindowTitle(int score, int cnt_level, int max_levels, int cnt_food,
                         int food_per_level, int fps);

private:
  SDL_Window *_sdl_window;
  SDL_Renderer *_sdl_renderer;

  const std::size_t _screen_width;
  const std::size_t _screen_height;
  const std::size_t _grid_width;
  const std::size_t _grid_height;
};

#endif