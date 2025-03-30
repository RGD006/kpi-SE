#pragma once
#include <SDL2/SDL_render.h>

class Canvas 
{
private:
    SDL_Point window_pos;
    SDL_Renderer *renderer;
    // std::queue<Object>
public:
    Canvas(SDL_Window *, SDL_Point);
    Canvas();
    void renderCanvas();
};
