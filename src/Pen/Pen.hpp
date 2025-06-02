#pragma once
#include <SDL2/SDL.h>
#include "Canvas.hpp"
#include "Shapes.hpp"

class Pen
{
private:
    color_t color;
    IObject *shape;
    Canvas *canvas;
    
    public:
    Pen();
    Pen(color_t);
    Pen(IObject *);
    Pen(color_t, IObject *);
    void changePen(IObject *);
    void deletePen();
    void eventHandler(void);
    void addCanvas(Canvas *canvas);
    IObject *drawShape(SDL_Point);
    ~Pen();
};