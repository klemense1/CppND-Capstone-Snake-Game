#include "renderer.h"
#include "snake.h"
#include <iostream>
#include <string>

using geometry::Point2d;
using geometry::Point2dInt;

Renderer::Renderer(const param::Settings &settings)
    : _screen_width(settings.kScreenWidth),
      _screen_height(settings.kScreenHeight), _grid_width(settings.kGridWidth),
      _grid_height(settings.kGridHeight) {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create Window
  _sdl_window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED,
                                 SDL_WINDOWPOS_CENTERED, _screen_width,
                                 _screen_height, SDL_WINDOW_SHOWN);

  if (nullptr == _sdl_window) {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create renderer
  _sdl_renderer = SDL_CreateRenderer(_sdl_window, -1, SDL_RENDERER_ACCELERATED);
  if (nullptr == _sdl_renderer) {
    std::cerr << "Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  _block.w = _screen_width / _grid_width;
  _block.h = _screen_height / _grid_height;
}

Renderer::~Renderer() {
  SDL_DestroyWindow(_sdl_window);
  SDL_DestroyRenderer(_sdl_renderer);
  SDL_Quit();
}

void Renderer::Render(Snake const &snake, std::shared_ptr<Food> const &food,
                      std::vector<std::shared_ptr<Obstacle>> const &obstacles) {
  // Clear screen
  SDL_SetRenderDrawColor(_sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(_sdl_renderer);

  // Render food
  food->Render(this);

  // Render fence
  for (const auto &obstacle : obstacles) {
    obstacle->Render(this);
  }

  snake.Render(this);

  // Update Screen
  SDL_RenderPresent(_sdl_renderer);
}

void Renderer::UpdateWindowTitle(int score, int cnt_level, int max_levels,
                                 int cnt_food, int food_per_level, int fps) {
  std::string title{
      "Snake Score: " + std::to_string(score) +
      " Level: " + std::to_string(cnt_level) + "/" +
      std::to_string(max_levels) + " #Food: " + std::to_string(cnt_food) + "/" +
      std::to_string(food_per_level) + " FPS: " + std::to_string(fps)};
  SDL_SetWindowTitle(_sdl_window, title.c_str());
}

template <typename T>
void Renderer::DrawRectangle(const Point2d<T> &point, const Colour &colour) {
  SDL_SetRenderDrawColor(_sdl_renderer, colour.red, colour.green, colour.blue,
                         colour.alpha);
  SDL_Rect block;
  block.w = _screen_width / _grid_width;
  block.h = _screen_height / _grid_height;
  block.x = static_cast<int>(point.x * block.w);
  block.y = static_cast<int>(point.y * block.h);
  SDL_RenderFillRect(_sdl_renderer, &block);
}

// explicit instantiations to circumvate declaration in header file
template void Renderer::DrawRectangle<int>(const Point2d<int> &point,
                                           const Colour &colour);
template void Renderer::DrawRectangle<float>(const Point2d<float> &point,
                                             const Colour &colour);