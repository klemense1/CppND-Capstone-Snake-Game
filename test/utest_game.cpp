#include "../src/controller.h"
#include "../src/game.h"
#include "../src/renderer.h"
#include "../src/settings.h"
#include "gtest/gtest.h"

param::Settings SetupTestSettings() {
  param::Settings settings = param::Settings();
  settings.kFramesPerSecond = 60;
  settings.kMsPerFrame = 1000 / settings.kFramesPerSecond;
  settings.kScreenWidth = 640 * 2;
  settings.kScreenHeight = 640;
  settings.kGridWidth = 32 * 2;
  settings.kGridHeight = 32;
  settings.maxLevels = 10;
  settings.foodPerLevel = 10;
  return settings;
}

class SnakeGameTest : public ::testing::Test {
protected:
  param::Settings settings = SetupTestSettings();
};

TEST_F(SnakeGameTest, TestRencererConstructor) {
  std::unique_ptr<Renderer> renderer = std::make_unique<Renderer>(settings);
}

TEST_F(SnakeGameTest, TestControllerConstructor) {
  std::unique_ptr<Controller> controller = std::make_unique<Controller>();
}

TEST_F(SnakeGameTest, TestGameConstructor) {
  std::unique_ptr<Game> game = std::make_unique<Game>(settings);
}