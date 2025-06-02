#pragma once
#include <SDL2/SDL_render.h>
#include <queue>
#include <list>

#include "Object.hpp"
#include "Pen.hpp"

class Canvas 
{
private:
    SDL_Point window_pos;
    SDL_Renderer *renderer;
    std::queue<IObject*> objects;
    Pen pen;

public:
    Canvas(SDL_Window *, SDL_Point);
    Canvas();
    void render();
    void addObject(IObject *);
    Pen getPen();
    size_t getNumberOfObjects();
};

