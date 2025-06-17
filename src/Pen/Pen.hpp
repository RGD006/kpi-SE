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
    bool start_move; // flag for indication if mouse move in drawing mode
    bool calculateScale(SDL_Rect scale, int &x, int &y);

public:
    Pen();
    Pen(color_t);
    Pen(IObject *);
    Pen(color_t, IObject *);
    void changeShape(IObject *);
    void increaseSize(u32);
    void decreaseSize(i32);
    void changeColor(u32);
    void deletePen();
    void eventMouseDown(void *);
    void eventMouseUp(void *);
    void eventMouseMove(void *);
    void addCanvas(Canvas *canvas);
    bool *getMoveState();
    IObject *getShape(SDL_Point);
    Canvas *getCanvas();
    ~Pen();
};