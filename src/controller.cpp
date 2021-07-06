#include "controller.h"
#include <iostream>
#include "SDL.h"
#include "snake.h"

void Controller::ChangeDirection(Snake *snake, Snake::Direction input,
                                 Snake::Direction opposite) const {
  if (snake->direction != opposite || snake->_size == 1) snake->direction = input;
  return;
}

void Controller::HandleInput(Snake::GameState &state, Snake *snake) const {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
      state = Snake::GameState::end;
    } else if (e.type == SDL_KEYDOWN) {
      switch (e.key.keysym.sym) {
        case SDLK_ESCAPE:
          state = Snake::GameState::end;
          break;
        case SDLK_SPACE:
          if (state == Snake::GameState::pause)
            state = Snake::GameState::run;
          else
            state = Snake::GameState::pause;
          break;
        case SDLK_UP:
          ChangeDirection(snake, Snake::Direction::kUp,
                          Snake::Direction::kDown);
          state = Snake::GameState::run;
          break;

        case SDLK_DOWN:
          ChangeDirection(snake, Snake::Direction::kDown,
                          Snake::Direction::kUp);
          state = Snake::GameState::run;
          break;

        case SDLK_LEFT:
          ChangeDirection(snake, Snake::Direction::kLeft,
                          Snake::Direction::kRight);
          state = Snake::GameState::run;
          break;

        case SDLK_RIGHT:
          ChangeDirection(snake, Snake::Direction::kRight,
                          Snake::Direction::kLeft);
          state = Snake::GameState::run;
          break;
      }
    }
  }
}