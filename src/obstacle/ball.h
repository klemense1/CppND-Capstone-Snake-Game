#ifndef OBSTACLE_BALL_H
#define OBSTACLE_BALL_H

#include "geometry.h"
#include "obstacle/obstacle.h"
#include "param.h"
#include "random_generator.h"
#include "snake.h"

class Ball : public Obstacle {
public:
  Ball(const Snake &snake, const param::Settings &settings);
  bool Update() override;
  void Render(Renderer *renderer) const override;
  bool CollidesWithSnakeHead(const Snake &snake) const override;
  bool CollidesWithSnake(const Snake &snake) const override;

private:
  void GenerateBall(const Snake &snake);
  geometry::Point2dFloat _pt;
  Rand_Int _random_w;
  geometry::Point2dInt _grid_size;
  int _dir_x;
  int _dir_y;
  float _speed;
};

#endif