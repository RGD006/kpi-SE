#include "Canvas.hpp"

Canvas::Canvas()
{

}

Canvas::Canvas(SDL_Window *window, SDL_Point center_point)
{
    renderer = SDL_CreateRenderer(window, 0, SDL_RENDERER_ACCELERATED);
}