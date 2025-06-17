#pragma once
#include "Pen.hpp"
#include "Object.hpp"
#include "Button.hpp"
#include <vector>

enum BUTTONEVENTS
{
   BUTTON_SAVE,
   BUTTON_CHANGE_COLOR_RED,
   BUTTON_CHANGE_COLOR_YELLOW,
   BUTTON_CHANGE_COLOR_BLUE,
   BUTTON_CHANGE_COLOR_GREEN,
   BUTTON_CHANGE_COLOR_PINK,
   BUTTON_CHANGE_COLOR_PURPLE,
   BUTTON_CHANGE_COLOR_WHITE,
   BUTTON_CHANGE_COLOR_GREY,
   BUTTON_CHANGE_COLOR_BLACK,
   BUTTON_CHANGE_COLOR_ERASER,
   BUTTON_INCREASE_PEN_SIZE,
   BUTTON_DECREASE_PEN_SIZE,
   BUTTON_BUF_SIZE,
};


extern u32 color_red;
extern u32 color_yellow;
extern u32 color_blue;
extern u32 color_green;
extern u32 color_pink;
extern u32 color_purple;
extern u32 color_white;
extern u32 color_grey;
extern u32 color_black;
extern u32 color_eraser;

extern SDL_Rect color_button_dest_red;
extern SDL_Rect color_button_dest_yellow;
extern SDL_Rect color_button_dest_blue;
extern SDL_Rect color_button_dest_green;
extern SDL_Rect color_button_dest_pink;
extern SDL_Rect color_button_dest_purple;
extern SDL_Rect color_button_dest_white;
extern SDL_Rect color_button_dest_grey;
extern SDL_Rect color_button_dest_black;
extern SDL_Rect color_button_dest_eraser;
extern SDL_Rect rect_increase_pen_size;
extern SDL_Rect rect_decrease_pen_size;