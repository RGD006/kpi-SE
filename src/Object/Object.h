#ifndef OBJECT_H
#define OBJECT_H

#include <stdint.h>

class Object
{
private:
  uint32_t x, y;
  uint32_t width, height;

public:
  Object(const uint32_t _x, const uint32_t _y, const uint32_t _width, const uint32_t _height);
  virtual void showObject();
  uint32_t getX();
  uint32_t getY();
  uint32_t getWidth();
  uint32_t getHeight();
};

#endif