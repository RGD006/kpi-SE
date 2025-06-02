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
        std::cerr << "New shape is NULL" << std::endl;
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
        std::cerr << "New shape is NULL" << std::endl;
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

void Pen::eventHandler(void)
{
    SDL_Event mouse_event;
    bool start_move = false;
    int x, y;
    while (SDL_PollEvent(&mouse_event))
    {
        if (mouse_event.type == SDL_MOUSEBUTTONDOWN)
        {
            start_move = true; 
            if (mouse_event.button.button == SDL_BUTTON_LEFT)
            {
                SDL_GetMouseState(&x, &y);
                canvas->addObject(drawShape(createPoint(x, y)));
                std::cout << "Mouse event: " << x << " " << y << std::endl;
            }
        }
        else if (mouse_event.type == SDL_MOUSEBUTTONUP)
        {
            start_move = false;
        }
        else if (mouse_event.type == SDL_MOUSEMOTION)
        {
            if (start_move)
            {
                SDL_GetMouseState(&x, &y);
                std::cout << "x: " << x << " " << "y: " << y << std::endl;
            }
        }
    }
}