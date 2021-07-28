#ifndef OBJECT_H
#define OBJECT_H

class Renderer;
class Snake;

class Object {
public:
  virtual bool CollidesWithSnakeHead(const Snake &snake) const = 0;
  virtual bool CollidesWithSnake(const Snake &snake) const = 0;
  virtual bool Update() = 0;
  virtual void Render(Renderer *renderer) const = 0;
};

#endif