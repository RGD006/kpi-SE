#include "EventHandler.hpp"
#include <iostream>

EventHandler::EventHandler()
{
}

event_function_t::event_function_t()
{
    this->arg = nullptr;
    this->function = nullptr;
}

event_function_t::event_function_t(std::function<void(void*)> function, void *arg)
{
    this->arg = arg;
    this->function = function;
}

void EventHandler::addEvent(u32 new_event, std::function<void(void *)> function, void *arg)
{
    events[new_event] = event_function_t(function, arg);
}

void EventHandler::run(void)
{
    while (SDL_PollEvent(&incoming_event))
    {
        // std::cout << "Event type: " << incoming_event.type << std::endl;
        if (events.contains(incoming_event.type))
        {
            // std::cout << "Handled event: " << incoming_event.type << std::endl;
            auto evnt = events.at(incoming_event.type);
            evnt.function(evnt.arg);
        }
    }
}