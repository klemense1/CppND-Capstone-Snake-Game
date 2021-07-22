#include "controller.h"
#include "SDL.h"
#include "snake.h"
#include <iostream>

Controller::OIMap Controller::_oppositeInputMapping = {
    {Snake::Direction::kUp, Snake::Direction::kDown},
    {Snake::Direction::kDown, Snake::Direction::kUp},
    {Snake::Direction::kLeft, Snake::Direction::kRight},
    {Snake::Direction::kRight, Snake::Direction::kLeft}};

void Controller::ChangeDirection(Snake *snake, Snake::Direction input) const {
  if (snake->_direction != _oppositeInputMapping[snake->_direction] ||
      snake->Size() == 1)
    snake->_direction = input;
  return;
}

void Controller::HandleInput(GameState &state, Snake *snake) const {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
      state = GameState::ending;
    } else if (e.type == SDL_KEYDOWN) {
      switch (e.key.keysym.sym) {
      case SDLK_ESCAPE:
        state = GameState::ending;
        break;
      case SDLK_SPACE:
        if (state == GameState::paused)
          state = GameState::running;
        else
          state = GameState::paused;
        break;
      case SDLK_UP:
        ChangeDirection(snake, Snake::Direction::kUp);
        state = GameState::running;
        break;

      case SDLK_DOWN:
        ChangeDirection(snake, Snake::Direction::kDown);
        state = GameState::running;
        break;

      case SDLK_LEFT:
        ChangeDirection(snake, Snake::Direction::kLeft);
        state = GameState::running;
        break;

      case SDLK_RIGHT:
        ChangeDirection(snake, Snake::Direction::kRight);
        state = GameState::running;
        break;
      }
    }
  }
}