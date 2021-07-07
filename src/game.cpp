#include "game.h"
#include "SDL.h"
#include <iostream>

Game::Game(std::size_t grid_width, std::size_t grid_height,
           std::size_t max_levels, std::size_t food_per_level)
    : _snake(std::make_unique<Snake>(grid_width, grid_height)), _food(),
      _cnt_level(1), _cnt_food(0), _max_levels(max_levels),
      _food_per_level(food_per_level), _engine(_dev()),
      _random_w(0, static_cast<int>(grid_width - 1)),
      _random_h(0, static_cast<int>(grid_height - 1)) {
  PlaceFence();
  PlaceFood();
}

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  Snake::GameState state = Snake::GameState::run;

  while (state != Snake::GameState::end && _cnt_level < _max_levels) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(state, _snake.get());
    if (state == Snake::GameState::run) {
      Update();
      renderer.Render(_snake, _food, _fence);

      frame_end = SDL_GetTicks();

      // Keep track of how long each loop through the input/update/render cycle
      // takes.
      frame_count++;
      frame_duration = frame_end - frame_start;

      // After every second, update the window title.
      if (frame_end - title_timestamp >= 1000) {
        renderer.UpdateWindowTitle(_score, _cnt_level, _max_levels, _cnt_food,
                                   _food_per_level, frame_count);
        frame_count = 0;
        title_timestamp = frame_end;
      }

      // If the time for this frame is too small (i.e. frame_duration is
      // smaller than the target ms_per_frame), delay the loop to
      // achieve the correct frame rate.
      if (frame_duration < target_frame_duration) {
        SDL_Delay(target_frame_duration - frame_duration);
      }
    }
  }
}

void Game::PlaceFood() {
  int x, y;
  while (true) {
    x = _random_w(_engine);
    y = _random_h(_engine);
    // Check that the location is not occupied by a snake item before placing
    // food.
    if (!_snake->SnakeCell(x, y)) {
      _food.x = x;
      _food.y = y;
      _cnt_food++;
      return;
    }
  }
}

void Game::PlaceFence() {
  // TODO: maybe do it in a class?
  // TODO: check half space where snake is, and place fence in other half
  // fill _fence
  _fence.clear();
  int x0 = _random_w(_engine);
  int y0 = _random_h(_engine);
  int x1, y1;

  // TODO: should become more dificult with each level
  for (int i = 0; i < 2; ++i) {
    if (i % 2 == 0) {
      x1 = _random_w(_engine);
      y1 = y0;
    } else {
      x1 = x0;
      y1 = _random_h(_engine);
    }
    // Check that the location is not occupied by a snake item before placing
    // food.
    for (int j = 0; j < std::max(x1 - x0, y1 - y0); ++j) {
      SDL_Point pt;
      pt.x = x0 + j / std::max(1, (x1 - x0));
      pt.y = y0 + j / std::max(1, (y1 - y0));
      _fence.push_back(pt);
    }
  }
}

bool Game::CollidingWithFence() {
  // Check if the snake has collided with fence.
  for (auto const &item : _fence) {
    // TODO: improve API to snake
    // cast to int necessary, as position of snake is float
    if (int(_snake->_head_x) == item.x && int(_snake->_head_y) == item.y) {
      return true;
    }
  }
  return false;
}

void Game::Update() {

  if (_cnt_food == 0)
    PlaceFence();

  if (!_snake->_alive)
    return;

  if (CollidingWithFence() == true)
    return;

  _snake->Update();

  int new_x = static_cast<int>(_snake->_head_x);
  int new_y = static_cast<int>(_snake->_head_y);

  // Check if there's food over here
  if (_food.x == new_x && _food.y == new_y) {
    _score++;
    if (_cnt_food == _food_per_level) {
      _cnt_level++;
      _cnt_food = 0;
    } else {
      PlaceFood();
    }
    // Grow snake and increase speed.
    _snake->GrowBody();
    _snake->_speed += 0.02;
  }
}

int Game::GetScore() const { return _score; }
int Game::GetSnakeSize() const { return _snake->_size; }
int Game::GetCntLevel() const { return _cnt_level; }
int Game::GetMaxLevels() const { return _max_levels; }
int Game::GetCntFood() const { return _cnt_food; }
int Game::GetFoodPerLevel() const { return _food_per_level; }