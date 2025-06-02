#pragma once
#include <SDL2/SDL_events.h>
#include <functional>
#include <typeof.hpp>
#include <map>

struct event_function_t 
{
    std::function<void(void*)> function;
    void *arg;
    event_function_t();
    event_function_t(std::function<void(void*)>, void *);
};

class EventHandler
{
private:
    SDL_Event incoming_event;
    std::map<u32, event_function_t> events;
public:
    EventHandler();
    void addEvent(u32, std::function<void(void*)>, void *);
    SDL_Event getEvent();
    void run(void);
};