#include "Object.h"
#include <SDL2/SDL.h>

Object::Object(const uint32_t _x, const uint32_t _y, const uint32_t _width, const uint32_t _height)
    : x(_x), y(_y), width(_width), height(_height)
{
}

uint32_t Object::getX() { return x; }
uint32_t Object::getY() { return y; }
uint32_t Object::getWidth() { return width; }
uint32_t Object::getHeight() { return height; }
void Object::showObject() {}