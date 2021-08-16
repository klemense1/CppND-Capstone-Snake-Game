#include "controller.h"
#include "game.h"
#include "param.h"
#include "renderer.h"
#include <iostream>
#include <memory>

int main() {
  param::Settings settings = param::Settings();
  settings.kFramesPerSecond = 60;
  settings.kMsPerFrame = 1000 / settings.kFramesPerSecond;
  settings.kScreenWidth = 640 * 2;
  settings.kScreenHeight = 640;
  settings.kGridWidth = 32 * 2;
  settings.kGridHeight = 32;
  settings.maxLevels = 9;
  settings.foodPerLevel = 2;
  settings.numCornersFence = 2;

  std::unique_ptr<Renderer> renderer = std::make_unique<Renderer>(settings);
  std::unique_ptr<Controller> controller = std::make_unique<Controller>();
  std::unique_ptr<Game> game = std::make_unique<Game>(settings);
  game->Run(*controller, *renderer);
  std::cout << *game;
  return 0;
}