#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <typeof.hpp>
#include <vector>

#include "Entity.hpp"
#include "EventHandler.hpp"
#include "Canvas.hpp"

class Window 
{
private:
    SDL_Window *window;
    SDL_Renderer *renderer; 
    EventHandler event_handler;
    Canvas canvas;
    std::vector<Entity*> ents;
    int width, height;
public:
    Window(const char *, u32, u32);
    void run(void);
};

void exitWindow(void *);