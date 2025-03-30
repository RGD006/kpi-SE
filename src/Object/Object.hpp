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
    u32 w;
    u32 h;

protected:
    IObject(u32, u32, SDL_Point);
    void setColor(color_t);
    color_t getColor(void);
    u32 getW(void);
    u32 getH(void);
    SDL_Point getCenterPoints(void);
    void drawObject(SDL_Renderer *);
};