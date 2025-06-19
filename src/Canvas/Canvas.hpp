#pragma once
#include <SDL2/SDL_render.h>
#include <queue>

#include "Object.hpp"

class Canvas
{
private:
    SDL_Point pos;
    SDL_Renderer *renderer;
    SDL_Rect canvas_destination;
    SDL_Rect aim_destination;
    SDL_Texture *background_texture; 
    SDL_Texture *canvas_texture;
    SDL_Texture *aim_texture; 
    int w, h;

public:
    Canvas(SDL_Renderer *, SDL_Point, int, int);
    Canvas();
    void render();
    SDL_Rect getDest();
    SDL_Renderer *getRenderer();
    SDL_Texture *getCanvasTexture();
    void setBackground(color_t, SDL_Rect *);
    void setAimTexture(Object *);
    void addObject(Object *);
};
