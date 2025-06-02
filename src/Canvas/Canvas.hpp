#pragma once
#include <SDL2/SDL_render.h>
#include <queue>

#include "Object.hpp"

class Canvas
{
private:
    SDL_Point window_pos;
    SDL_Renderer *renderer;
    std::queue<IObject *> objects;
    SDL_Texture *canvas_texture;
    int pos_x, pos_y, w, h;

public:
    Canvas(SDL_Window *, SDL_Point, int, int, int, int);
    Canvas();
    void render();
    void addObject(IObject *);
    size_t getNumberOfObjects();
};
