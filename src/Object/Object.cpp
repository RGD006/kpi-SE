#include "Object.hpp"

color_t::color_t(u8 _r, u8 _g, u8 _b, u8 _a)
    : r(_r), g(_g), b(_b), a(_a)
{
}

color_t::color_t(u32 rgba)
{
    r = (rgba >> 24) & 0xFF;
    g = (rgba >> 16) & 0xFF;
    b = (rgba >> 8) & 0xFF;
    a = rgba & 0xFF;
}

color_t::color_t()
{
    *this = color_t(0xFFFFFFFF);
}

IObject::IObject()
{
}

IObject::IObject(u32 _w, u32 _h, SDL_Point _center_point)
    : w(_w), h(_h), center_point(_center_point)
{
}

SDL_Point createPoint(i32 x, i32 y)
{
    SDL_Point tmp;
    tmp.x = x;
    tmp.y = y;
    return tmp;
}

void IObject::setColor(color_t _color) { color = _color; }
color_t IObject::getColor(void) { return color; }
u32 IObject::getW(void) { return w; }
u32 IObject::getH(void) { return h; }
SDL_Point IObject::getCenterPoints(void) { return center_point; }
void IObject::drawObject(SDL_Renderer *) {}
void IObject::setCenterPoints(SDL_Point new_points) { center_point = new_points; }

