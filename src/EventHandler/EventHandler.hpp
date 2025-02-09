#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include <SDL2/SDL.h>

class EventHandler
{
private:
    SDL_Event event;
public:
    EventHandler();
    int32_t getEvent();
};

#endif