#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_events.h>
#include "typeof.hpp"

class Entity
{
protected:
    SDL_Rect source_rect, destination_rect;
    SDL_Event event;
    SDL_Renderer *renderer;
    SDL_Texture *texture;

public:
    Entity(i32 event, SDL_Rect source_rect, SDL_Rect destination_rect, SDL_Renderer *window_render);
    Entity(i32 event, SDL_Rect source_rect, SDL_Rect destination_rect, SDL_Renderer *window_render, SDL_Texture *texture);
    Entity(i32 event, SDL_Rect source_rect, SDL_Rect destination_rect, SDL_Renderer *window_render, const char *path_to_texture);
    Entity(i32 event, SDL_Rect source_rect, SDL_Rect destination_rect, SDL_Renderer *window_render, u32 color);
    virtual void setTexture(SDL_Texture *texture);
    virtual void setTexture(const char *path);
    virtual void setTexture(u32 color);
    virtual void render(void);
    ~Entity();
};