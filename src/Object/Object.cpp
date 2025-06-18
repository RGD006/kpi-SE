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

Object::Object()
{
}

Object::Object(i32 _w, i32 _h, SDL_Point _center_point)
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

SDL_Rect createRect(i32 x, i32 y, i32 w, i32 h)
{
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;
    return rect;
}

bool isEmptyRect(SDL_Rect rect)
{
    SDL_Rect empty_rect = {
        .x = 0,
        .y = 0,
        .w = 0,
        .h = 0,
    };

    return memcmp(&rect, &empty_rect, sizeof(SDL_Rect)) == 0;
}

void Object::setW(i32 width)
{
    w = width;
}

void Object::setH(i32 height)
{
    h = height;
}

void Object::setColor(color_t _color) { color = _color; }
color_t Object::getColor(void) { return color; }
i32 Object::getW(void) { return w; }
i32 Object::getH(void) { return h; }
SDL_Point Object::getCenterPoints(void) { return center_point; }
void Object::render(SDL_Renderer *) {}
void Object::setCenterPoints(SDL_Point new_points) { center_point = new_points; }

