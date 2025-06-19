#pragma once
#include <SDL2/SDL_render.h>
#include <queue>

#include "Object.hpp"
#include "Entity.hpp"

class Canvas : public Entity
{
private:
    SDL_Rect aim_destination;
    SDL_Texture *background_texture; 
    SDL_Texture *canvas_texture;
    SDL_Texture *aim_texture; 

public:
    Canvas(SDL_Renderer *, SDL_Point, int, int);
    Canvas();
    void render();
    SDL_Texture *getCanvasTexture();
    void setBackground(color_t, SDL_Rect *);
    void setAimTexture(Object *);
    void addObject(Object *);
};
