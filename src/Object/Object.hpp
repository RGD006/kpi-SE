#pragma once
#include <SDL2/SDL_render.h>
#include <typeof.hpp>

struct color_t
{
    u8 r, g, b, a;
    color_t(u8, u8, u8, u8);
    color_t(u32);
    color_t();
};

class IObject
{
protected:
    color_t color;
    SDL_Point center_point;
    i32 w;
    i32 h;

public:
    IObject();
    IObject(u32, u32, SDL_Point);
    virtual void setColor(color_t);
    virtual color_t getColor(void);
    virtual u32 getW(void);
    virtual u32 getH(void);
    virtual SDL_Point getCenterPoints(void);
    virtual void drawObject(SDL_Renderer *);
};

SDL_Point createPoint(i32, i32);