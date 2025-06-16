#include "ButtonEvents.hpp"

u32 color_red = 0xFF0000FF;
u32 color_yellow = 0xFFFF00FF;
u32 color_blue = 0x0000FFFF;
u32 color_green = 0x00FF00FF;
u32 color_pink = 0xFF66FFFF;
u32 color_purple = 0x990099FF;
u32 color_white = 0xFFFFFFFF;
u32 color_grey = 0x606060FF;
u32 color_black = 0x000000FF;

SDL_Rect color_button_dest_red = {
    .x = 0,
    .y = 0,
    .w = 50,
    .h = 50,
};

SDL_Rect color_button_dest_yellow = {
    .x = 50,
    .y = 0,
    .w = 50,
    .h = 50,
};

SDL_Rect color_button_dest_blue = {
    .x = 100,
    .y = 0,
    .w = 50,
    .h = 50,
};

SDL_Rect color_button_dest_green = {
    .x = 150,
    .y = 0,
    .w = 50,
    .h = 50,
};

SDL_Rect color_button_dest_pink = {
    .x = 200,
    .y = 0,
    .w = 50,
    .h = 50,
};

SDL_Rect color_button_dest_purple = {
    .x = 250,
    .y = 0,
    .w = 50,
    .h = 50,
};

SDL_Rect color_button_dest_white = {
    .x = 300,
    .y = 0,
    .w = 50,
    .h = 50,
};

SDL_Rect color_button_dest_grey = {
    .x = 350,
    .y = 0,
    .w = 50,
    .h = 50,
};

SDL_Rect color_button_dest_black = {
    .x = 400,
    .y = 0,
    .w = 50,
    .h = 50,
};

void changePenColor(Pen *pen, u32 color)
{
    pen->getShape(createPoint(0, 0))->setColor(color);
}