#include "Rectangle.hpp"
#include <cassert>

void Rectangle::showObject()
{
    assert(surface && "object doesn't have surface");
    rect = {.x = x, .y = y, .w = width, .h = height};
    SDL_FillRect(surface, &rect, color);
}

void Rectangle::setColor(uint32_t _color)
{
    assert(surface && "object doesn't have surface");
    color = SDL_MapRGB(surface->format,
                       ((_color >> 16) & 0xFF),
                       ((_color >> 8) & 0xFF),
                       (_color & 0xFF));
}

Rectangle::Rectangle(const int32_t _x, const int32_t _y,
                     const int32_t _w, const int32_t _h)
    : Object(_x, _y, _w, _h)
{
}