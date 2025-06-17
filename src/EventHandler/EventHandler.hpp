#pragma once
#include <SDL2/SDL_events.h>
#include <functional>
#include <typeof.hpp>
#include <vector>
#include <map>

#include "Mouse.hpp"
#include "Button.hpp"

#define SDL_NO_BUTTON (0)
#define LISTEN_ALWAYS (UINT32_MAX)

struct event_function_t
{
    std::function<void(void *)> function;
    void *arg;
    u32 button;
    event_function_t();
    event_function_t(std::function<void(void *)>, void *);
    event_function_t(std::function<void(void *)>, void *, u32);
};

class EventHandler
{
private:
    Mouse mouse;
    SDL_Event incoming_event;
    std::map<u32, std::vector<event_function_t>> events;
    std::vector<event_function_t> listen_always_functions;
    std::vector<Button*> buttons;

public:
    EventHandler();
    void addEvent(u32, std::function<void(void *)>, void *);
    Mouse *getMouse(void);
    void addButton(Button*);
    SDL_Event getEvent();
    void run(void);
};