#include "Rectangle.hpp"
#include <iostream>

Rectangle::Rectangle(u32 w, u32 h, SDL_Point center_point)
    : Object(w, h, center_point)
{
}

void Rectangle::render(SDL_Renderer *renderer)
{
    SDL_Rect rect = {.x = center_point.x, .y = center_point.y, .w = w, .h = h};
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(renderer, &rect);
}