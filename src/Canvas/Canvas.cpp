#include "Canvas.hpp"
#include <iostream>

Canvas::Canvas()
{
}

Canvas::Canvas(SDL_Window *window, SDL_Point center_point, int _w, int _h)
    : w(_w), h(_h)
{
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer)
    {
        std::cerr << "Error with init renderer: " << SDL_GetError() << std::endl;
        exit(EXIT_FAILURE);
    }

    canvas_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, _w, _h);
    background_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, _w, _h);

    SDL_SetTextureBlendMode(canvas_texture, SDL_BLENDMODE_BLEND);
    SDL_SetTextureBlendMode(background_texture, SDL_BLENDMODE_BLEND);
}

// set in one color background_texture
void Canvas::setBackground(color_t color, SDL_Rect *rect)
{
    SDL_SetRenderTarget(renderer, background_texture);
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    if (rect)
        SDL_RenderFillRect(renderer, rect);
    else
        SDL_RenderClear(renderer);

    SDL_SetRenderTarget(renderer, nullptr);
}

void Canvas::addObject(IObject *object)
{
    SDL_SetRenderTarget(renderer, canvas_texture);
    object->drawObject(renderer);
    SDL_SetRenderTarget(renderer, nullptr);
}

void Canvas::render()
{
    SDL_RenderCopy(renderer, background_texture, nullptr, nullptr); // draw background_texture
    SDL_RenderCopy(renderer, canvas_texture, nullptr, nullptr);     // draw canvas
    SDL_RenderPresent(renderer);
}
