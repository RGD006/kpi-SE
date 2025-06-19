#include "Canvas.hpp"
#include <iostream>

#define MAX_QUEUE_SIZE (15)

Canvas::Canvas()
    : Entity(createRect(0, 0, 0, 0), nullptr)
{
}

Canvas::Canvas(SDL_Renderer *window_renderer, SDL_Point start_point, int _w, int _h)
    : Entity(createRect(start_point.x, start_point.y, _w, _h), window_renderer)
{
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
    if (rect->w != destination_rect.w || rect->h != destination_rect.h)
    {
        rect->w = destination_rect.w;
        rect->h = destination_rect.h;
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

void Canvas::saveCanvasRedo(SDL_Texture *texture)
{
    SDL_Texture *new_prev_texture = Entity::copyTexture(renderer, texture, destination_rect.w, destination_rect.h);

    if (prev_canvas_texture.size() <= MAX_QUEUE_SIZE)
    {
        prev_canvas_texture.push_front(new_prev_texture);
    }
    else
    {
        SDL_Texture *delete_prev_texture = prev_canvas_texture.front();
        prev_canvas_texture.pop_back();
        SDL_DestroyTexture(delete_prev_texture);
        prev_canvas_texture.push_front(new_prev_texture);
    }
}

void Canvas::saveCanvasUndo(SDL_Texture *texture)
{
    SDL_Texture *new_prev_texture = Entity::copyTexture(renderer, texture, destination_rect.w, destination_rect.h);

    std::cout << "New object undo" << std::endl;

    if (undo_canvas_texture.size() <= MAX_QUEUE_SIZE)
    {
        undo_canvas_texture.push_front(new_prev_texture);
    }
    else
    {
        SDL_Texture *delete_undo_texture = prev_canvas_texture.front();
        undo_canvas_texture.pop_back();
        SDL_DestroyTexture(delete_undo_texture);
        undo_canvas_texture.push_front(new_prev_texture);
    }
}

void Canvas::render()
{
    SDL_RenderCopy(renderer, background_texture, nullptr, &destination_rect); // draw background_texture
    SDL_RenderCopy(renderer, canvas_texture, nullptr, &destination_rect);     // draw canvas

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

SDL_Texture *Canvas::getCanvasTexture()
{
    return canvas_texture;
}

void Canvas::undo(void)
{
    if (!undo_canvas_texture.empty())
    {
        SDL_Texture *prev = undo_canvas_texture.front();
        undo_canvas_texture.pop_front();
        
        std::cout << "Delete undo" << std::endl;

        canvas_texture = Entity::copyTexture(renderer, prev, destination_rect.w, destination_rect.h); 

        saveCanvasRedo(canvas_texture);

        SDL_DestroyTexture(prev);
    }
}

void Canvas::redo(void)
{
    if (!prev_canvas_texture.empty())
    {
        SDL_Texture *redo_tex = prev_canvas_texture.front();
        prev_canvas_texture.pop_front();

        canvas_texture = Entity::copyTexture(renderer, redo_tex, destination_rect.w, destination_rect.h);

        saveCanvasUndo(canvas_texture);

        SDL_DestroyTexture(redo_tex);
    }
}