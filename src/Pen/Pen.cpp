#include "Pen.hpp"
#include "SDL2/SDL_events.h"
#include "ButtonEvents.hpp"
#include <cassert>
#include <bitset>
#include <iostream>
#include <algorithm>

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

    x = (x - scale.x) * getCanvas()->getDest().w / scale.w;
    y = (y - scale.y) * getCanvas()->getDest().h / scale.h;

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
    shape->setStartPoints(position);
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
    return getShape(createPoint(0, 0))->getColor() == color_white;
}

void Pen::listenEvents(void *arg)
{
    if (!mouse)
        throw "No pinned mouse";

    const std::bitset<MOUSE_STATE_SIZE> mouse_states = mouse->getAllStates();
    SDL_Rect mouse_tip_scaled = *mouse->getTipPos();
    SDL_Rect mouse_tip = *mouse->getTipPos();

    if (!calculateScale(canvas->getDest(), mouse_tip_scaled.x, mouse_tip_scaled.y))
    {
        canvas->setAimTexture(nullptr);
        return;
    }

    switch (draw_status)
    {
    case PEN_STATUS_DRAW_PIXEL:
        shape->setStartPoints(createPoint(mouse_tip_scaled.x, mouse_tip_scaled.y));

        if (mouse_states[MOUSE_HOLDING])
        {
            start_move = true;
            canvas->addObject(shape);
        }
        else if (mouse_states[MOUSE_END_CLICK])
        {
            start_move = false;
            canvas->saveCanvasTexture();
        }

        if (mouse_states[MOUSE_MOVING] && mouse_states[MOUSE_HOLDING])
        {
            canvas->addObject(shape);
        }

        shape->setStartPoints(createPoint(mouse_tip.x, mouse_tip.y));
        canvas->setAimTexture(shape);
        continueRender();

        break;

    case PEN_STATUS_DRAW_SHAPE:
        if (mouse_states[MOUSE_START_CLICK] && mouse_states[MOUSE_HOLDING])
        {
            start_draw_shape_x = mouse_tip_scaled.x;
            start_draw_shape_y = mouse_tip_scaled.y;
            aim_start_draw_shape_x = mouse_tip.x;
            aim_start_draw_shape_y = mouse_tip.y;
            start_move = true;
        }
        else if (mouse_states[MOUSE_MOVING] && mouse_states[MOUSE_HOLDING])
        {
            i32 x, y, w, h;
            x = std::min(start_draw_shape_x, mouse_tip_scaled.x);
            y = std::min(start_draw_shape_y, mouse_tip_scaled.y);
            w = std::abs(mouse_tip_scaled.x - start_draw_shape_x);
            h = std::abs(mouse_tip_scaled.y - start_draw_shape_y);

            shape->setStartPoints(createPoint(x, y));
            shape->setW(w);
            shape->setH(h);
        }

        if (!mouse_states[MOUSE_HOLDING] && mouse_states[MOUSE_END_CLICK] && start_move)
        {
            i32 x, y, w, h;
            x = std::min(start_draw_shape_x, mouse_tip_scaled.x);
            y = std::min(start_draw_shape_y, mouse_tip_scaled.y);
            w = std::abs(mouse_tip_scaled.x - start_draw_shape_x);
            h = std::abs(mouse_tip_scaled.y - start_draw_shape_y);

            shape->setStartPoints(createPoint(x, y));
            shape->setW(w);
            shape->setH(h);
            start_move = false;
            canvas->addObject(getShape(*shape->getStartPoints()));
            canvas->saveCanvasTexture();
            canvas->setAimTexture(nullptr);
            aim_start_draw_shape_x = 0;
            aim_start_draw_shape_y = 0;
            start_draw_shape_x = 0;
            start_draw_shape_y = 0;
        }

        if (mouse_states[MOUSE_HOLDING] && start_move)
        {
            i32 x, y, w, h;
            x = std::min(aim_start_draw_shape_x, mouse_tip.x);
            y = std::min(aim_start_draw_shape_y, mouse_tip.y);
            w = std::abs(mouse_tip.x - aim_start_draw_shape_x);
            h = std::abs(mouse_tip.y - aim_start_draw_shape_y);

            shape->setStartPoints(createPoint(x, y));
            shape->setW(w);
            shape->setH(h);

            shape->setStartPoints(createPoint(x, y));
            canvas->setAimTexture(shape);
            
            continueRender();
        }
        break;
    case PEN_STATUS_DRAW_TEXTURE:
        break;
    case PEN_STATUS_DRAW_NO:
        break;
    }
}

// when mouse don't move SDL2 don't send event
// => send event which indicates that object is still drawing
void Pen::continueRender()
{
    SDL_Event event_continue_render;
    event_continue_render.type = SDL_MOUSEMOTION;
    SDL_PushEvent(&event_continue_render);
}

void Pen::changeStatus(PENSTATUS new_status)
{
    draw_status = new_status;
}

PENSTATUS Pen::getStatus()
{
    return draw_status;
}