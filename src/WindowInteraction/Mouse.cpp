#include "Mouse.hpp"
#include <iostream>
#include <SDL2/SDL_events.h>

using namespace std;

#define SHORT_CLICK_TIMEOUT_MS (100)

// TODO: fix bug with mouse release

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

SDL_Rect *Mouse::getTipPos()
{
    return tip;
}

u32 Mouse::getState(MOUSESTATE state)
{
    return mouse_state[state];
}

void Mouse::setState(MOUSESTATE state, u32 value)
{
    mouse_state[state] = value;
}

void Mouse::setClickStartTime(void)
{
    const auto sys_time_epoch = chrono::system_clock::now().time_since_epoch();
    start_click_time_ms = chrono::duration_cast<chrono::milliseconds>(sys_time_epoch).count();
}

void Mouse::setClickEndTime(void)
{
    const auto sys_time_epoch = chrono::system_clock::now().time_since_epoch();
    end_click_time_ms = chrono::duration_cast<chrono::milliseconds>(sys_time_epoch).count();
}

void Mouse::pollEvents(SDL_Event *event)
{
    switch (event->type)
    {
    case SDL_MOUSEBUTTONDOWN:
        if (event->button.button == SDL_BUTTON_LEFT)
        {
            setClickStartTime();
            mouse_state[MOUSE_HOLDING] = 1;
            SDL_GetMouseState(&tip->x, &tip->y);
        }
        else if (event->button.button == SDL_BUTTON_RIGHT)
        {
            setClickStartTime();
            mouse_state[MOUSE_HOLDING] = 1;
            SDL_GetMouseState(&tip->x, &tip->y);
        }
        break;
    case SDL_MOUSEBUTTONUP:
        if (event->button.button == SDL_BUTTON_LEFT)
        {
            setClickEndTime();
            mouse_state[MOUSE_HOLDING] = 0;
            mouse_state[MOUSE_CLICK] = 1;
            SDL_GetMouseState(&tip->x, &tip->y);
        }
        else if (event->button.button == SDL_BUTTON_RIGHT)
        {
            setClickEndTime();
            mouse_state[MOUSE_HOLDING] = 1;
            mouse_state[MOUSE_CLICK] = 1;
            SDL_GetMouseState(&tip->x, &tip->y);
        }
        break;
    case SDL_MOUSEMOTION:
        // do smth
        break;
    default:
        break;
    }
}
