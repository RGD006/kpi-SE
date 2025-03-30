#pragma once
#include <SDL2/SDL.h>
#include <typeof.hpp>
#include "EventHandler.hpp"
#include "Canvas.hpp"

class Window 
{
private:
    SDL_Window *window;
    EventHandler event_handler;
    Canvas canvas;
public:
    Window(const char *, u32, u32);
    void showWindow(void);
};

void exitWindow(void *);