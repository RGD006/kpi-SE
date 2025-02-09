#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Object.hpp"

class Rectangle : public Object
{
    SDL_Rect rect;
    uint32_t color;
public:
    Rectangle(const int32_t _x, const int32_t _y,
              const int32_t _w, const int32_t _h);
    void setColor(uint32_t _color);
    void showObject() override;
};

#endif