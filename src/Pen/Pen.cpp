#include "Pen.hpp"
#include "SDL2/SDL_events.h"
#include <cassert>
#include <iostream>

Pen::Pen()
{
    color = color_t(0x0000000);
    shape = new Circle(5, createPoint(0, 0), true);
}

Pen::Pen(color_t _color)
{
    color = _color;
    shape = new Circle(5, createPoint(0, 0), true);
}

Pen::Pen(IObject *_shape)
{
    color = color_t(0x0000000);
    if (_shape)
    {
        shape = _shape;
    }
    else
    {
        std::cerr << "New shape is nullptr" << std::endl;
        shape = new Circle(5, createPoint(0, 0), true);
    }
}

Pen::Pen(color_t _color, IObject *_shape)
{
    if (_shape)
    {
        color = _color;
        shape = _shape;
    }
    else
    {
        std::cerr << "New shape is nullptr" << std::endl;
        shape = new Circle(5, createPoint(0, 0), true);
    }
}

void Pen::changePen(IObject *new_shape)
{
    assert(new_shape);
    shape = new_shape;
}

void Pen::deletePen()
{
    delete shape;
}

IObject *Pen::drawShape(SDL_Point position)
{
    shape->setCenterPoints(position);
    return shape;
}

Pen::~Pen()
{
    delete shape;
}

void Pen::addCanvas(Canvas *canvas)
{
    this->canvas = canvas;
}

void Pen::eventMouseDown(void *arg)
{
    bool *start_move = reinterpret_cast<bool *>(arg);
    int x, y;
    *start_move = true;
    SDL_GetMouseState(&x, &y);
    canvas->addObject(drawShape(createPoint(x, y)));
    // std::cout << "Mouse down event: " << x << " " << y << std::endl;
}

void Pen::eventMouseMove(void *arg)
{
    bool *start_move = reinterpret_cast<bool *>(arg);
    int x, y;
    if (*start_move)
    {
        SDL_GetMouseState(&x, &y);
        canvas->addObject(drawShape(createPoint(x, y)));
        // std::cout << "Mouse continue draw event: " << x << " " << y << std::endl;
    }
}

void Pen::eventMouseUp(void *arg)
{
    bool *start_move = reinterpret_cast<bool *>(arg);
    if (*start_move)
    {
        *start_move = false;
        // std::cout << "Stop draw event" << std::endl;
    }
}

bool *Pen::getMoveState() { return &start_move; }