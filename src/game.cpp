#include "game.h"
#include "SDL.h"
#include <iostream>

using geometry::Point2dInt;

Game::Game(const param::Settings &settings)
    : _snake(
          std::make_unique<Snake>(settings.kGridWidth, settings.kGridHeight)),
      _food(), _cnt_level(1), _cnt_food(0), _settings(settings),
      _engine(_dev()), _random_w(0, static_cast<int>(settings.kGridWidth - 1)),
      _random_h(0, static_cast<int>(settings.kGridHeight - 1)) {
  PlaceFence();
  PlaceFood();
}

void Game::Run(Controller const &controller, Renderer &renderer) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  Snake::GameState state = Snake::GameState::run;

  while (state != Snake::GameState::end && _cnt_level < _settings.maxLevels) {
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
        renderer.UpdateWindowTitle(_score, _cnt_level, _settings.maxLevels,
                                   _cnt_food, _settings.foodPerLevel,
                                   frame_count);
        frame_count = 0;
        title_timestamp = frame_end;
      }

      // If the time for this frame is too small (i.e. frame_duration is
      // smaller than the target ms_per_frame), delay the loop to
      // achieve the correct frame rate.
      if (frame_duration < _settings.kMsPerFrame) {
        SDL_Delay(_settings.kMsPerFrame - frame_duration);
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
      Point2dInt pt;
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
    if (_cnt_food == _settings.foodPerLevel) {
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

bool Game::ReachedGameEnding() const {
  return (_cnt_level == _settings.maxLevels);
}
int Game::GetScore() const { return _score; }
int Game::GetSnakeSize() const { return _snake->_size; }
int Game::GetCntLevel() const { return _cnt_level; }
int Game::GetMaxLevels() const { return _settings.maxLevels; }
int Game::GetCntFood() const { return _cnt_food; }
int Game::GetFoodPerLevel() const { return _settings.foodPerLevel; }

std::ostream &operator<<(std::ostream &os, const Game &game) {
  if (game.ReachedGameEnding()) {
    os << "Game has terminated successfully!\n";
  } else {
    os << "Game has terminated early!\n";
  }
  os << "Score: " << game.GetScore() << "\nLevel: " << game.GetCntLevel()
     << "/" << game.GetMaxLevels() << "\nSize: " << game.GetSnakeSize()
     << "\n";
  return os;
}