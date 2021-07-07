#include "controller.h"
#include "game.h"
#include "renderer.h"
#include <iostream>

int main() {
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{1280};
  constexpr std::size_t kScreenHeight{640};
  constexpr std::size_t kGridWidth{32};
  constexpr std::size_t kGridHeight{32};
  constexpr int maxLevels{3};    // 10};
  constexpr int foodPerLevel{2}; // 10};

  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  Controller controller;
  Game game(kGridWidth, kGridHeight, maxLevels, foodPerLevel);
  game.Run(controller, renderer, kMsPerFrame);
  if (game.GetCntLevel() < game.GetMaxLevels()) {
    std::cout << "Game has terminated early!\n";
  } else {
    std::cout << "Game has terminated successfully!\n";
  }
  std::cout << "Score: " << game.GetScore() << "\n";
  std::cout << "Level: " << game.GetCntLevel() << "/" << game.GetMaxLevels()
            << "\n";
  std::cout << "Size: " << game.GetSnakeSize() << "\n";
  return 0;
}