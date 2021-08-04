#ifndef OBJECT_H
#define OBJECT_H

#include <memory>

class Renderer;
// class Colour;
class Snake;

struct Colour {
  Colour(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha)
      : red(red), green(green), blue(blue), alpha(alpha) {}
  uint8_t red;
  uint8_t green;
  uint8_t blue;
  uint8_t alpha;
};

class Object {
public:
  virtual bool CollidesWithSnakeHead(const Snake &snake) const = 0;
  virtual bool CollidesWithSnake(const Snake &snake) const = 0;
  virtual bool Update() = 0;
  virtual void Render(Renderer *renderer) const = 0;
};

#endif