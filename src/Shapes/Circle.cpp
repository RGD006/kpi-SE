#include "Circle.hpp"
#include <cmath>
#include <iostream>

Circle::Circle(u32 r, SDL_Point center_point, bool filled)
    : Object(r, r, center_point), radius_x(r), radius_y(r), fill_full(filled)
{
}

Circle::Circle(u32 rx, u32 ry, SDL_Point center_point, bool filled)
    : Object(rx, ry, center_point), radius_x(rx), radius_y(ry), fill_full(filled)
{
}

void Circle::render(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    i32 center_x = center_point.x + radius_x, center_y = center_point.y + radius_y;

    if (fill_full)
    {
        for (int y = -static_cast<int>(radius_y); y <= static_cast<int>(radius_y); y++)
        {
            for (int x = -static_cast<int>(radius_x); x <= static_cast<int>(radius_x); x++)
            {
                float norm_x = static_cast<float>(x) / radius_x;
                float norm_y = static_cast<float>(y) / radius_y;
                if ((norm_x * norm_x + norm_y * norm_y) <= 1.0f)
                {
                    SDL_RenderDrawPoint(renderer, center_x + x, center_y + y);
                }
            }
        }
    }
    else
    {
        const int segments = 360;
        for (int i = 0; i < segments; i++)
        {
            float theta = (float)i * 2.0f * M_PI / segments;
            int x = static_cast<int>(radius_x * cosf(theta));
            int y = static_cast<int>(radius_y * sinf(theta));
            SDL_RenderDrawPoint(renderer, center_point.x + x, center_point.y + y);
        }
    }
}

i32 Circle::getW(void)
{
    return radius_x * 2;
}

i32 Circle::getH(void)
{
    return radius_y * 2;
}

void Circle::setW(i32 value)
{
    radius_x = value / 2;
}

void Circle::setH(i32 value)
{
    radius_y = value / 2;
}