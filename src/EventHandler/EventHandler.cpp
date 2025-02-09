#include "EventHandler.hpp"

EventHandler::EventHandler()
{
}

int32_t EventHandler::getEvent()
{
    for (;SDL_PollEvent(&event);)
    {
        return event.type;
    }

    return UINT32_MAX;    
}
