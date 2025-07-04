#pragma once
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_events.h>
#include <chrono>
#include <bitset>
#include "typeof.hpp"

enum MOUSESTATE
{
    MOUSE_HOLDING,
    MOUSE_START_CLICK,
    MOUSE_END_CLICK, 
    MOUSE_SHORT_CLICK,
    MOUSE_LONG_CLICK,
    MOUSE_MOVING,
    MOUSE_STATE_SIZE
};

class Mouse
{
private:

    SDL_Rect *cursor, *tip;
    i64 start_click_time_ms, end_click_time_ms;
    std::bitset<MOUSE_STATE_SIZE> state;
    
public:
    SDL_Rect* getTipPos();
    u32 getState(MOUSESTATE state);
    void setState(MOUSESTATE state, u32 value);
    std::bitset<MOUSE_STATE_SIZE> getAllStates();
    void pollEvents(SDL_Event *event);
    void endCallback(void);
    void setClickStartTime(void);
    void setClickEndTime(void);
    Mouse();
    ~Mouse();
};