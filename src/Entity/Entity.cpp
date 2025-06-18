#include "Entity.hpp"
#include "Object.hpp"
#include <SDL2/SDL_image.h>

Entity::Entity(i32 button_event, SDL_Rect source, SDL_Rect destination, SDL_Renderer *render)
{
    if (!render)
        throw "window renderer is nullptr";

    texture = nullptr;
    event.type = SDL_USEREVENT;
    event.user.code = button_event;
    renderer = render;
    source_rect = source;
    destination_rect = destination;
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
    // own function to draw
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
    SDL_Rect rect = {0, 0, destination_rect.w, destination_rect.h};
    texture = SDL_CreateTexture(renderer,
                                SDL_PIXELFORMAT_RGBA8888,
                                SDL_TEXTUREACCESS_TARGET,
                                rect.w, rect.h);
    color_t rect_color(color);
    SDL_SetRenderTarget(renderer, texture);
    SDL_SetRenderDrawColor(renderer, rect_color.r, rect_color.g, rect_color.b, rect_color.a);
    SDL_RenderClear(renderer);
    SDL_RenderFillRect(renderer, &rect);
}

Entity::~Entity()
{
    if (texture)
    {
        SDL_DestroyTexture(texture);
    }
}