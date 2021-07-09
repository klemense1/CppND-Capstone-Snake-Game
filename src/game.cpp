#include "game.h"
#include "SDL.h"
#include <iostream>

using geometry::Point2dInt;

Game::Game(const param::Settings &settings)
    : _snake(
          std::make_unique<Snake>(settings.kGridWidth, settings.kGridHeight)),
      _food(nullptr), _cnt_level(0), _cnt_food(0), _settings(settings),
      _random_generator() {
  InitializeLevel();
}

void Game::Run(Controller const &controller, Renderer &renderer) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  Snake::GameState state = Snake::GameState::run;

  while (state != Snake::GameState::end && _cnt_level <= _settings.maxLevels) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(state, _snake.get());
    if (state == Snake::GameState::run) {

      Update();

      renderer.Render(*_snake, _food, _obstacles);

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

void Game::InitializeLevel() {
  _obstacles.clear();
  _food = std::make_shared<Apple>(_random_generator, *_snake, _settings);
  _obstacles.emplace_back(
      std::make_shared<Fence>(_random_generator, _settings));
  _cnt_level++;
}

void Game::Update() {

  if (!_snake->_alive)
    return;

  for (auto &obstacle : _obstacles) {
    if (obstacle->CollidesWithSnake(*_snake)) {
      std::cout << "Obstacle collides with snake ... ending game\n";
      return;
    }
  }

  _snake->Update();

  // Check if there's food over here
  if (_food) {
    if (_food->CollidesWithSnakeHead(*_snake)) {
      _score++;
      _cnt_food++;
      if (_cnt_food == _settings.foodPerLevel) {
        _cnt_food = 0;
        InitializeLevel();
      } else {
        std::cout << "Update Creating Food\n";
        _food = std::make_shared<Apple>(_random_generator, *_snake, _settings);
      }
      // Grow snake and increase speed.
      _snake->GrowBody();
      _snake->_speed += 0.02;
    }
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
  os << "Score: " << game.GetScore() << "\nLevel: " << game.GetCntLevel() << "/"
     << game.GetMaxLevels() << "\nSize: " << game.GetSnakeSize() << "\n";
  return os;
}