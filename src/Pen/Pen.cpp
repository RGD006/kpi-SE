#include "Pen.hpp"
#include "SDL2/SDL_events.h"
#include <cassert>
#include <bitset>
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

Pen::Pen(Object *_shape)
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

Pen::Pen(color_t _color, Object *_shape)
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

Canvas *Pen::getCanvas()
{
    return canvas;
}

bool Pen::calculateScale(SDL_Rect scale, int &x, int &y)
{
    if (x < scale.x || x > scale.x + scale.w ||
        y < scale.y || y > scale.y + scale.h)
    {
        return false;
    }

    x = (x - scale.x) * getCanvas()->getScale().w / scale.w;
    y = (y - scale.y) * getCanvas()->getScale().h / scale.h;

    return true;
}

void Pen::changeShape(Object *new_shape)
{
    assert(new_shape);
    shape = new_shape;
}

void Pen::deletePen()
{
    delete shape;
}

Object *Pen::getShape(SDL_Point position)
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

bool *Pen::getMoveState() { return &start_move; }

void Pen::increaseSize(u32 value)
{
    Object *shape = getShape(createPoint(0, 0));
    u32 old_w = shape->getW(), old_h = shape->getH();
    shape->setW(old_w + value);
    shape->setH(old_h + value);
}

void Pen::decreaseSize(i32 value)
{
    Object *shape = getShape(createPoint(0, 0));
    i32 old_w = shape->getW(), old_h = shape->getH();
    if (old_w - value > 0 && old_h - value > 0)
    {
        shape->setW(old_w - value);
        shape->setH(old_h - value);
    }
}

void Pen::changeColor(u32 color)
{
    getShape(createPoint(0, 0))->setColor(color);
}

void Pen::pinMouse(Mouse *mouse)
{
    this->mouse = mouse;
}

bool Pen::nowEraser(void)
{
    return getShape(createPoint(0, 0))->getColor().a == 0x00;
}

void Pen::listenEvents(void *arg)
{
    if (!mouse)
        throw "No pinned mouse";

    const std::bitset<MOUSE_STATE_SIZE> mouse_states = mouse->getAllStates();
    SDL_Rect mouse_tip = *mouse->getTipPos();

    if (!calculateScale(canvas->getScale(), mouse_tip.x, mouse_tip.y))
    {
        return;
    }

    if (mouse_states[MOUSE_HOLDING])
    {
        start_move = true;
        canvas->addObject(getShape(createPoint(mouse_tip.x, mouse_tip.y)));
    }
    else
    {
        start_move = false;
    }

    if (mouse_states[MOUSE_MOVING] && mouse_states[MOUSE_HOLDING])
    {
        canvas->addObject(getShape(createPoint(mouse_tip.x, mouse_tip.y)));
    }
}