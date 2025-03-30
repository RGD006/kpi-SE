#include "Canvas.hpp"
#include <iostream>

Canvas::Canvas()
{
}

Canvas::Canvas(SDL_Window *window, SDL_Point center_point)
{
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer)
    {
        std::cerr << "Error with init renderer: " << SDL_GetError() << std::endl;
        exit(EXIT_FAILURE);
    }
}

void Canvas::addObject(IObject *object)
{
    objects.push_back(object);
}

void Canvas::render()
{
    for (IObject *object : objects)
    {
        object->drawObject(renderer);
    }

    SDL_RenderPresent(renderer);
}