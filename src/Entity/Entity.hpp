#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_events.h>
#include "typeof.hpp"

#define NO_EVENT (-1)

class Entity
{
protected:
    SDL_Rect source_rect, destination_rect;
    SDL_Event event;
    SDL_Renderer *renderer;
    SDL_Texture *texture;

public:
    Entity(SDL_Rect destination_rect, SDL_Renderer *window_renderer);
    Entity(i32 event, SDL_Rect source_rect, SDL_Rect destination_rect, SDL_Renderer *window_render);
    Entity(i32 event, SDL_Rect source_rect, SDL_Rect destination_rect, SDL_Renderer *window_render, SDL_Texture *texture);
    Entity(i32 event, SDL_Rect source_rect, SDL_Rect destination_rect, SDL_Renderer *window_render, const char *path_to_texture);
    Entity(i32 event, SDL_Rect source_rect, SDL_Rect destination_rect, SDL_Renderer *window_render, u32 color);
    virtual void setTexture(SDL_Texture *texture);
    virtual void setTexture(const char *path);
    virtual void setTexture(u32 color);
    virtual SDL_Texture *getTexture(void);
    virtual void listenEvent(void);
    virtual void sendEvent(void);
    virtual void render(void);
    virtual SDL_Renderer *getRenderer(void);
    virtual SDL_Rect getDest(void);
    static SDL_Texture *copyTexture(SDL_Renderer *renderer, SDL_Texture *source, i32 width, i32 height);
    ~Entity();
};