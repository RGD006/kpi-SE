#pragma once
#include <SDL2/SDL_events.h>
#include <functional>
#include <typeof.hpp>
#include <vector>
#include <map>

#include "Mouse.hpp"
#include "Button.hpp"

#define SDL_NO_BUTTON (0)

struct event_function_t 
{
    std::function<void(void*)> function;
    void *arg;
    u32 button;
    event_function_t();
    event_function_t(std::function<void(void*)>, void *);
    event_function_t(std::function<void(void*)>, void *, u32);
};

class EventHandler
{
private:
    Mouse mouse;
    SDL_Event incoming_event;
    std::map<u32, std::vector<event_function_t>> events;
    std::map<u32, std::vector<event_function_t>> button_events;
    std::vector<Button> io_buttons;
public:
    EventHandler();
    void addEvent(u32, std::function<void(void*)>, void *);
    void addButtonEvent(u32, u32, std::function<void(void*)>, void *);
    SDL_Event getEvent();
    void run(void);
};