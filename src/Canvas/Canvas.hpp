#pragma once
#include <SDL2/SDL_render.h>
#include <queue>

#include "Object.hpp"

class Canvas
{
private:
    SDL_Point pos;
    SDL_Renderer *renderer;
    SDL_Rect scale;
    SDL_Texture *background_texture; 
    SDL_Texture *canvas_texture;
    int w, h;

public:
    Canvas(SDL_Renderer *, SDL_Point, int, int);
    Canvas();
    void render();
    SDL_Rect getScale();
    void setBackground(color_t, SDL_Rect *);
    void addObject(IObject *);
};
