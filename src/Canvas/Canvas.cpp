#include "Canvas.hpp"
#include <iostream>

Canvas::Canvas()
{
}

Canvas::Canvas(SDL_Renderer *window_renderer, SDL_Point start_point, int _w, int _h)
    : pos(start_point), w(_w), h(_h)
{
    canvas_destination = (SDL_Rect){
        .x = start_point.x,
        .y = start_point.y,
        .w = w,
        .h = h,
    }; // canvas_destination for correct drawing in canvas

    renderer = window_renderer;
    if (!renderer)
    {
        std::cerr << "Error with init renderer: " << SDL_GetError() << std::endl;
        exit(EXIT_FAILURE);
    }

    canvas_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, _w, _h);
    background_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, _w, _h);
    aim_texture = nullptr;

    SDL_SetTextureBlendMode(canvas_texture, SDL_BLENDMODE_BLEND);
    SDL_SetTextureBlendMode(background_texture, SDL_BLENDMODE_BLEND);
}

// set in one color background_texture
void Canvas::setBackground(color_t color, SDL_Rect *rect)
{
    // resize background size for canvas size
    if (rect->w != w || rect->h != h)
    {
        rect->w = w;
        rect->h = h;
    }

    SDL_SetRenderTarget(renderer, background_texture);
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    if (rect)
        SDL_RenderFillRect(renderer, rect);
    else
        SDL_RenderClear(renderer);

    SDL_SetRenderTarget(renderer, nullptr);
}

void Canvas::addObject(Object *object)
{
    SDL_SetRenderTarget(renderer, canvas_texture);
    object->render(renderer);
    SDL_SetRenderTarget(renderer, nullptr);
}

void Canvas::render()
{
    SDL_RenderCopy(renderer, background_texture, nullptr, &canvas_destination); // draw background_texture
    SDL_RenderCopy(renderer, canvas_texture, nullptr, &canvas_destination);     // draw canvas

    if (aim_texture)
    {
        SDL_RenderCopy(renderer, aim_texture, nullptr, &aim_destination);
    }

    SDL_SetRenderTarget(renderer, nullptr);
}

void Canvas::setAimTexture(Object *aim)
{
    if (aim)
    {
        aim_destination = {
            .x = aim->getStartPoints()->x,
            .y = aim->getStartPoints()->y,
            .w = aim->getW(),
            .h = aim->getH(),
        };

        if (!aim_texture)
        {
            aim_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, aim_destination.w, aim_destination.h);
            SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
        }
        else
        {
            SDL_SetRenderTarget(renderer, aim_texture);
            SDL_RenderClear(renderer);
            aim->render(renderer);
            SDL_SetRenderTarget(renderer, nullptr);
        }
    }
    else
    {
        SDL_SetRenderTarget(renderer, aim_texture);
        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
        SDL_RenderFillRect(renderer, &aim_destination);
        SDL_SetRenderTarget(renderer, nullptr);
        SDL_DestroyTexture(aim_texture);
        aim_texture = nullptr;
    }
}

SDL_Rect Canvas::getDest()
{
    return canvas_destination;
}

SDL_Renderer *Canvas::getRenderer()
{
    return renderer;
}

SDL_Texture *Canvas::getCanvasTexture()
{
    return canvas_texture;
}
