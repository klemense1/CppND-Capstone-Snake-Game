#ifndef RENDERER_H
#define RENDERER_H

#include "SDL.h"
#include "food/food.h"
#include "geometry.h"
#include "obstacle/obstacle.h"
#include "param.h"
#include <memory>
#include <vector>

class Snake;
class Renderer {
public:
  Renderer(const param::Settings &settings);
  Renderer(Renderer const &renderer) = delete;            // copy constructor
  Renderer(Renderer &&renderer);                          // move constructor
  Renderer &operator=(const Renderer &renderer) = delete; // copy assignment
  Renderer &operator=(Renderer &&renderer);               // move assignment

  ~Renderer();

  void Render(Snake const &snake, std::shared_ptr<Food> const &food,
              std::vector<std::shared_ptr<Obstacle>> const &obstacles);

  void UpdateWindowTitle(int score, int cnt_level, int max_levels, int cnt_food,
                         int food_per_level, int fps);

  template <typename T>
  void DrawRectangle(const geometry::Point2d<T> &point, const Colour &colour);

  const SDL_Window *GetSDLWindow() const { return _sdl_window; }
  const SDL_Renderer *GetSDLRenderer() const { return _sdl_renderer; }

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