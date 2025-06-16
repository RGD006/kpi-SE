#include "Mouse.hpp"

using namespace std;

#define CLICK_TIME_MS (100)

Mouse::Mouse()
{
    cursor = new SDL_Rect;
    cursor->w = 50;
    cursor->h = 50;
    cursor->x = 0;
    cursor->y = 0;

    tip = new SDL_Rect;

    tip->w = 1;
    tip->h = 1;
    tip->x = 0;
    tip->y = 0;
}

Mouse::~Mouse()
{
    delete cursor;
    delete tip;
}

SDL_Rect *Mouse::interaction()
{
    return tip;
}

void *Mouse::mousePressLeft()
{
    const auto sys_time_epoch = chrono::system_clock::now().time_since_epoch();
    start_click_time_ms = chrono::duration_cast<chrono::milliseconds>(sys_time_epoch).count();

    is_holding = true;

    return nullptr;
}

void *Mouse::mousePressRight()
{
    return nullptr;
}

void *Mouse::mouseReleaseLeft()
{
    const auto sys_time_epoch = chrono::system_clock::now().time_since_epoch();
    end_click_time_ms = chrono::duration_cast<chrono::milliseconds>(sys_time_epoch).count();
    is_holding = false;

    if (end_click_time_ms - start_click_time_ms <= CLICK_TIME_MS) 
    {
        is_short_click = true;
        return reinterpret_cast<void *>(tip);
    }
    else
    {
        is_long_click = true;
        return reinterpret_cast<void *>(tip);
    } 
}

void *Mouse::mouseReleaseRight()
{
    return nullptr;
}
