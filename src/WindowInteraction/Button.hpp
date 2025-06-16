#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_events.h>
#include "typeof.hpp"
#include "Mouse.hpp"

class Button
{
private:
    SDL_Rect s_rect, d_rect;
    SDL_Event event;
    SDL_Renderer *renderer;
    SDL_Texture *texture;

public:
    Button(u32 event, SDL_Rect _size, SDL_Rect _dest, SDL_Renderer *_window_render);
    Button(u32 event, SDL_Rect _size, SDL_Rect _dest, SDL_Renderer *_window_render, SDL_Texture *texture);
    Button(u32 event, SDL_Rect _size, SDL_Rect _dest, SDL_Renderer *_window_render, const char *path_to_texture);
    void setTexture(SDL_Texture *texture);
    void setTexture(const char *path);
    void render(void);
    void listenMouse(Mouse &mouse);
    ~Button();
};
