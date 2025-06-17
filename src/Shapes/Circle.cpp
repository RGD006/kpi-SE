#include "Circle.hpp"
#include <cmath>
#include <iostream>

Circle::Circle(u32 r, SDL_Point center_point, bool filled = false)
    : IObject(r * 2, r * 2, center_point), fill_full(filled), radius(r)
{
}

void Circle::drawObject(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    if (fill_full)
    {
        for (u32 w = 0; w < radius * 2; w++)
        {
            for (u32 h = 0; h < radius * 2; h++)
            {
                u32 dx = radius - w;
                u32 dy = radius - h;
                if ((dx * dx + dy * dy) <= (radius * radius))
                {
                    SDL_RenderDrawPoint(renderer, center_point.x + dx, center_point.y + dy);
                }
            }
        }
    }
    else
    {
        const u32 segments = 360;

        for (u32 i = 0; i < segments; i++)
        {
            float theta = (float)i * (2.0f * M_PI / segments);
            u32 x = (u32)(radius * cosf(theta));
            u32 y = (u32)(radius * sinf(theta));
            SDL_RenderDrawPoint(renderer, center_point.x + x, center_point.y + y);
        }
    }
}

u32 Circle::getW(void)
{
    return radius;
}

u32 Circle::getH(void)
{
    return radius;
}

void Circle::setW(u32 value)
{
    radius = value;
}

void Circle::setH(u32 value)
{
    radius = value;
}