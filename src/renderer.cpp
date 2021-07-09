#include "renderer.h"
#include <iostream>
#include <string>

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
  SDL_Rect block;
  block.w = _screen_width / _grid_width;
  block.h = _screen_height / _grid_height;

  // Clear screen
  SDL_SetRenderDrawColor(_sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(_sdl_renderer);

  // Render food
  food->Render(_sdl_renderer, block);

  // Render fence
  for (const auto &obstacle : obstacles) {
    obstacle->Render(_sdl_renderer, block);
  }

  // Render snake's body
  SDL_SetRenderDrawColor(_sdl_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  for (Point2dInt const &point : snake._body) {
    block.x = point.x * block.w;
    block.y = point.y * block.h;
    SDL_RenderFillRect(_sdl_renderer, &block);
  }

  // Render snake's head
  block.x = static_cast<int>(snake._head_x) * block.w;
  block.y = static_cast<int>(snake._head_y) * block.h;
  if (snake._alive) {
    SDL_SetRenderDrawColor(_sdl_renderer, 0x00, 0x7A, 0xCC, 0xFF);
  } else {
    SDL_SetRenderDrawColor(_sdl_renderer, 0xFF, 0x00, 0x00, 0xFF);
  }
  SDL_RenderFillRect(_sdl_renderer, &block);

  // Update Screen
  SDL_RenderPresent(_sdl_renderer);
}

// TODO: use this in fence and food
void Renderer::DrawRectangle(geometry::Point2dInt point, Uint8 r, Uint8 g,
                             Uint8 b, Uint8 a) {
  SDL_Rect block;
  block.w = _screen_width / _grid_width;
  block.h = _screen_height / _grid_height;
  block.x = point.x * block.w;
  block.y = point.y * block.h;
  SDL_RenderFillRect(_sdl_renderer, &block);
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
