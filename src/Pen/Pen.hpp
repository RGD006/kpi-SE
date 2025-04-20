#pragma once
#include <SDL2/SDL.h>
#include "Shapes.hpp"
#include "EventHandler.hpp"

class Pen
{
private:
    color_t color;
    IObject *shape;

public:
    Pen(color_t);
    Pen(IObject *);
    Pen(color_t, IObject *);
    void changePen(IObject *);
    IObject *getShape();
};