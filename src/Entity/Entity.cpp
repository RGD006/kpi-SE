#include "Entity.hpp"
#include "Object.hpp"
#include <iostream>
#include <SDL2/SDL_image.h>

Entity::Entity(i32 button_event, SDL_Rect source, SDL_Rect destination, SDL_Renderer *render)
{
    texture = nullptr;
    event.type = SDL_USEREVENT;
    event.user.code = button_event;
    event.user.data1 = nullptr;
    renderer = render;
    source_rect = source;
    destination_rect = destination;
    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_NONE);
}

Entity::Entity(SDL_Rect destination_rect, SDL_Renderer *window_renderer)
    : Entity(NO_EVENT, createRect(0, 0, 0, 0), destination_rect, window_renderer)
{
    texture = nullptr;
}

Entity::Entity(i32 button_event, SDL_Rect source, SDL_Rect destination, SDL_Renderer *render, SDL_Texture *texture)
    : Entity(button_event, source, destination, render)
{
    setTexture(texture);
}

Entity::Entity(i32 button_event, SDL_Rect source, SDL_Rect destination, SDL_Renderer *render, const char *path_to_texture)
    : Entity(button_event, source, destination, render)
{
    setTexture(path_to_texture);
}

Entity::Entity(i32 button_event, SDL_Rect source, SDL_Rect destination, SDL_Renderer *render, u32 color)
    : Entity(button_event, source, destination, render)
{
    setTexture(color);
}

void Entity::render()
{
    if (isEmptyRect(source_rect))
    {
        SDL_RenderCopy(renderer, texture, nullptr, &destination_rect);
    }
    else
    {
        SDL_RenderCopy(renderer, texture, &source_rect, &destination_rect);
    }
}

void Entity::setTexture(SDL_Texture *texture)
{
    this->texture = texture;
}

void Entity::setTexture(const char *path)
{
    if (texture)
        SDL_DestroyTexture(texture);

    texture = IMG_LoadTexture(renderer, path);
}

void Entity::setTexture(u32 color)
{
    if (texture)
        SDL_DestroyTexture(texture);

    texture = SDL_CreateTexture(renderer,
                                SDL_PIXELFORMAT_RGBA8888,
                                SDL_TEXTUREACCESS_TARGET,
                                destination_rect.w, destination_rect.h);

    color_t rect_color(color);
    SDL_SetRenderTarget(renderer, texture);
    SDL_SetRenderDrawColor(renderer, rect_color.r, rect_color.g, rect_color.b, rect_color.a);
    SDL_RenderClear(renderer);
    SDL_RenderFillRect(renderer, &destination_rect);
    SDL_SetRenderTarget(renderer, nullptr);
}

void Entity::listenEvent(void)
{
    // own function realization
}

void Entity::sendEvent(void)
{
    // own function realization
}

Entity::~Entity()
{
    if (texture)
    {
        SDL_DestroyTexture(texture);
    }
}

SDL_Rect Entity::getDest(void)
{
    return destination_rect;
}

SDL_Texture *Entity::getTexture(void)
{
    return texture;
}

SDL_Renderer *Entity::getRenderer(void)
{
    return renderer;
}

SDL_Texture *Entity::copyTexture(SDL_Renderer *renderer, SDL_Texture *source, i32 width, i32 height)
{
    SDL_Texture *target = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, width, height);
    SDL_SetTextureBlendMode(target, SDL_BLENDMODE_BLEND);
    SDL_Texture *old_target = SDL_GetRenderTarget(renderer);
    SDL_SetRenderTarget(renderer, target);
    SDL_RenderCopy(renderer, source, nullptr, nullptr);
    SDL_SetRenderTarget(renderer, old_target);
    return target;
}