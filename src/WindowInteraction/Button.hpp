#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_events.h>
#include "typeof.hpp"
#include "Entity.hpp"
#include "Mouse.hpp"

class Button : public Entity
{
private:

public:
    Button(i32 event, SDL_Rect _size, SDL_Rect _dest, SDL_Renderer *_window_render);
    Button(i32 event, SDL_Rect _size, SDL_Rect _dest, SDL_Renderer *_window_render, SDL_Texture *texture);
    Button(i32 event, SDL_Rect _size, SDL_Rect _dest, SDL_Renderer *_window_render, const char *path_to_texture);
    Button(i32 event, SDL_Rect _size, SDL_Rect _dest, SDL_Renderer *_window_render, u32 color);
    void render(void);
    void listenEvent(Mouse &mouse);
    ~Button();
};
