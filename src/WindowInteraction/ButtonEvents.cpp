#include "ButtonEvents.hpp"
#include <iostream>

u32 color_red = 0xFF0000FF;
u32 color_yellow = 0xFFFF00FF;
u32 color_blue = 0x0000FFFF;
u32 color_green = 0x00FF00FF;
u32 color_pink = 0xFF66FFFF;
u32 color_purple = 0x990099FF;
u32 color_white = 0xFFFFFFFF;
u32 color_grey = 0x606060FF;
u32 color_black = 0x000000FF;
u32 color_eraser = 0x0;

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

SDL_Rect color_button_dest_eraser = {
    .x = 100,
    .y = 50,
    .w = 50,
    .h = 50,
};

SDL_Rect rect_increase_pen_size = {
    .x = 0,
    .y = 50,
    .w = 50,
    .h = 50,
};

SDL_Rect rect_decrease_pen_size = {
    .x = 50,
    .y = 50,
    .w = 50,
    .h = 50,
};

SDL_Rect rect_change_pen_rect = {
    .x = 150,
    .y = 50,
    .w = 50,
    .h = 50, 
};

SDL_Rect rect_change_pen_circ = {
    .x = 200,
    .y = 50,
    .w = 50,
    .h = 50,
};