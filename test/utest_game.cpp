#include "../src/controller.h"
#include "../src/game.h"
// #include "../src/renderer.h"
#include "../src/food.h"
#include "../src/obstacle.h"
#include "../src/param.h"
#include "../src/random_generator.h"
#include "../src/snake.h"
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
  Renderer renderer = Renderer(settings);
}

TEST_F(SnakeGameTest, TestControllerConstructor) {
  Controller controller = Controller();
}

TEST_F(SnakeGameTest, TestGameConstructor) {
  Game game = Game(settings);
}

TEST_F(SnakeGameTest, TestRandomGenerator) {
  Rand_Int rnd = Rand_Int(10, 10);
  EXPECT_EQ(rnd(), 10);
}

TEST_F(SnakeGameTest, TestSnakeConstructor) {
  Snake snake = Snake(settings.kGridHeight, settings.kGridWidth);
}

TEST_F(SnakeGameTest, TestAppleConstructor) {
  Snake snake = Snake(settings.kGridHeight, settings.kGridWidth);
  Apple apple = Apple(snake, settings);
}

TEST_F(SnakeGameTest, TestFenceConstructor) {
  Fence fence = Fence(settings);
}