#pragma once
#include <SDL2/SDL_render.h>
#include <queue>
#include <list>

#include "Object.hpp"

class Canvas 
{
private:
    SDL_Point window_pos;
    SDL_Renderer *renderer;
    std::queue<IObject*> objects;
public:
    Canvas(SDL_Window *, SDL_Point);
    Canvas();
    void render();
    void addObject(IObject *);
    size_t getNumberOfObjects();
};

