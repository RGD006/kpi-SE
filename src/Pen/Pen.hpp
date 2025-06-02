#pragma once
#include <SDL2/SDL.h>
#include "Shapes.hpp"
#include "EventHandler.hpp"

class Pen
{
private:
    color_t color;
    IObject *shape;
    EventHandler *bind_event_handler;

public:
    Pen();
    Pen(color_t);
    Pen(IObject *);
    Pen(color_t, IObject *);
    void changePen(IObject *);
    void deletePen();
    IObject *drawShape(SDL_Point);
    void bindEventHandler(EventHandler *);
    void mouseButtonEvent(void *);
    ~Pen();
};