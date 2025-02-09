#ifndef OBJECT_H
#define OBJECT_H

#include <stdint.h>
#include <SDL2/SDL.h>

class Object
{
protected:
  int32_t x, y;
  int32_t width, height;
  SDL_Surface *surface;

public:
  Object(const int32_t _x, const int32_t _y,
         const int32_t _width, const int32_t _height);
  ~Object();
  virtual void showObject();
  void setSurface(SDL_Surface *surface);
  int32_t getX();
  int32_t getY();
  int32_t getWidth();
  int32_t getHeight();
  SDL_Surface *getSurface();
};

#endif