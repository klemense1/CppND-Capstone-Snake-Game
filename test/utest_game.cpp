#include "../src/controller.h"
#include "../src/food/apple.h"
#include "../src/food/food.h"
#include "../src/game.h"
#include "../src/geometry.h"
#include "../src/obstacle/fence.h"
#include "../src/obstacle/obstacle.h"
#include "../src/param.h"
#include "../src/random_generator.h"
#include "../src/snake.h"
#include "gtest/gtest.h"

using namespace geometry;

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
  settings.numCornersFence = 2;
  return settings;
}

class SnakeGameTest : public ::testing::Test {
protected:
  param::Settings settings = SetupTestSettings();
};

TEST_F(SnakeGameTest, TestRencererConstructor) {
  Renderer renderer = Renderer(settings);
  EXPECT_TRUE(nullptr != renderer.GetSDLWindow());
  EXPECT_TRUE(nullptr != renderer.GetSDLRenderer());
}

TEST_F(SnakeGameTest, TestRandomGenerator) {
  Rand_Int rnd = Rand_Int(10, 10);
  EXPECT_EQ(rnd(), 10);
}

TEST_F(SnakeGameTest, TestSnakeConstructor) {
  Snake snake = Snake(settings);
  EXPECT_LE(snake.GetHead().x, settings.kGridWidth);
  EXPECT_LE(snake.GetHead().y, settings.kGridHeight);
}

TEST_F(SnakeGameTest, TestAppleConstructor) {
  Snake snake = Snake(settings);
  Apple apple = Apple(snake, settings);
  auto point = apple.GetPosition();
  EXPECT_LE(point.x, settings.kGridWidth);
  EXPECT_LE(point.y, settings.kGridHeight);
}

TEST_F(SnakeGameTest, TestFenceConstructor) {
  Snake snake = Snake(settings);
  Fence fence = Fence(snake, settings);
  auto pts = fence.GetPoints();
  for (auto p : pts) {
    EXPECT_LE(p.x, settings.kGridWidth);
    EXPECT_LE(p.y, settings.kGridHeight);
  }
}

TEST_F(SnakeGameTest, CollideInt) {
  Point2dInt p1{1, 2};
  Point2dInt p2{2, 1};
  EXPECT_TRUE(Collides(p1, p1));
  EXPECT_TRUE(Collides(p2, p2));
  EXPECT_FALSE(Collides(p1, p2));
  EXPECT_FALSE(Collides(p2, p1));
}

TEST_F(SnakeGameTest, CollideMixed) {
  Point2dInt p1{1, 2};
  Point2dFloat p2{1.0, 2.0};
  Point2dFloat p3{2.0, 1.0};
  EXPECT_TRUE(Collides(p1, p2));
  EXPECT_FALSE(Collides(p1, p3));
}
