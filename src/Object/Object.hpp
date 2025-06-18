#pragma once
#include <SDL2/SDL_render.h>
#include <typeof.hpp>

struct color_t
{
    u8 r, g, b, a;
    color_t(u8, u8, u8, u8);
    color_t(u32);
    color_t();
    operator u32() const
    {
        return (r << 24) | (g << 16) | (b << 8) | a;
    }
};

class Object
{
protected:
    color_t color;
    SDL_Point center_point;
    i32 w;
    i32 h;

public:
    Object();
    Object(i32, i32, SDL_Point);
    virtual void setColor(color_t);
    virtual color_t getColor(void);
    virtual i32 getW(void);
    virtual i32 getH(void);
    virtual void setW(i32);
    virtual void setH(i32);
    virtual SDL_Point getCenterPoints(void);
    virtual void render(SDL_Renderer *);
    virtual void setCenterPoints(SDL_Point);
};

SDL_Point createPoint(i32, i32);
SDL_Rect createRect(i32, i32, i32, i32);
bool isEmptyRect(SDL_Rect rect);