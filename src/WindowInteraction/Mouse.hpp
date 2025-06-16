#pragma once
#include <SDL2/SDL_render.h>
#include <chrono>
#include "typeof.hpp"

class Mouse
{
private:
    SDL_Rect *cursor, *tip;
    i64 start_click_time_ms, end_click_time_ms;
    bool is_holding; 

    bool is_short_click;
    bool is_long_click;
    
public:
    SDL_Rect* interaction();
    void* mouseMove();
    void* mousePressLeft();
    void* mousePressRight();
    void* mouseReleaseLeft();
    void* mouseReleaseRight();
    Mouse();
    ~Mouse();
};