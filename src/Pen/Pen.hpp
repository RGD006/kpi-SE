#pragma once
#include <SDL2/SDL.h>
#include <Mouse.hpp>
#include "Canvas.hpp"
#include "Shapes.hpp"

enum PENSTATUS
{
    PEN_STATUS_DRAW_PIXEL,
    PEN_STATUS_DRAW_SHAPE,
    PEN_STATUS_DRAW_TEXTURE,
    PEN_STATUS_FILL,
    PEN_STATUS_DRAW_NO,
};

class Pen
{
private:
    color_t color;
    PENSTATUS draw_status;
    Object *shape;
    Canvas *canvas;
    Mouse *mouse;
    bool start_move; // flag for indication if mouse move in drawing mode
    i32 start_draw_shape_x, start_draw_shape_y;
    i32 aim_start_draw_shape_x, aim_start_draw_shape_y;
    bool calculateScale(SDL_Rect scale, int &x, int &y);
    void continueRender();

public:
    Pen();
    Pen(color_t);
    Pen(Object *);
    Pen(color_t, Object *);
    void pinMouse(Mouse *mouse);
    void listenEvents(void *arg);
    void changeShape(Object *);
    void changeStatus(PENSTATUS new_status);
    PENSTATUS getStatus();
    void increaseSize(u32);
    void decreaseSize(i32);
    void changeColor(u32);
    void deletePen();
    bool nowEraser(void);
    void addCanvas(Canvas *canvas);
    bool *getMoveState();
    Object *getShape(SDL_Point);

    Canvas *getCanvas();
    ~Pen();
};