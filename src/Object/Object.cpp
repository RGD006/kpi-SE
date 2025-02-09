#include "Object.hpp"
#include <SDL2/SDL.h>

Object::Object(const int32_t _x, const int32_t _y,
               const int32_t _width, const int32_t _height)
    : x(_x), y(_y), width(_width), height(_height)
{
}

Object::~Object()
{
}

int32_t Object::getX() { return x; }
int32_t Object::getY() { return y; }
int32_t Object::getWidth() { return width; }
int32_t Object::getHeight() { return height; }
void Object::setSurface(SDL_Surface *surface) { this->surface = surface; }
SDL_Surface *Object::getSurface() { return surface; }
void Object::showObject() {}