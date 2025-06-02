#include "Pen.hpp"
#include "SDL2/SDL_events.h"
#include "Canvas.hpp"
#include <iostream>
#include <cassert>

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

void Pen::bindEventHandler(EventHandler *event_handler)
{
    bind_event_handler = event_handler;
}

void Pen::mouseButtonEvent(void *arg)
{
   Canvas *canvas = reinterpret_cast<Canvas *>(arg);
   u32 pos_x = bind_event_handler->getEvent().button.x;
   u32 pos_y = bind_event_handler->getEvent().button.y;
   canvas->addObject(drawShape(createPoint(pos_x, pos_y)));
}