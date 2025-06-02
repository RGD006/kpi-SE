#include "Canvas.hpp"
#include <iostream>

Canvas::Canvas()
{
}

Canvas::Canvas(SDL_Window *window, SDL_Point center_point, int _x, int _y, int _w, int _h)
    : pos_x(_x), pos_y(_y), w(_w), h(_y)
{
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer)
    {
        std::cerr << "Error with init renderer: " << SDL_GetError() << std::endl;
        exit(EXIT_FAILURE);
    }

    std::cout << _w << " " << _h << std::endl;

    canvas_texture = SDL_CreateTexture(
        renderer,
        SDL_PIXELFORMAT_RGBA8888,
        SDL_TEXTUREACCESS_TARGET,
        _w,
        _h);
}

void Canvas::addObject(IObject *object)
{
    objects.push(object);
}

void Canvas::render()
{
    SDL_RenderClear(renderer);
    SDL_SetRenderTarget(renderer, canvas_texture);
    
    while (!objects.empty())
    {
        objects.front()->drawObject(renderer);
        objects.pop();
    }

    SDL_SetRenderTarget(renderer, NULL);
    SDL_RenderCopy(renderer, canvas_texture, NULL, NULL);
    SDL_RenderPresent(renderer);
}

size_t Canvas::getNumberOfObjects()
{
    return objects.size();
}
